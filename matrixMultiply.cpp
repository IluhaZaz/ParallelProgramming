#include <vector>
#include <iostream>
#include <mpi.h>

using namespace std;

class MatrixMultiplicator {
public:
    static vector<vector<float>> multiply(const vector<vector<float>>& m1, const vector<vector<float>>& m2) 
    {
        int world_size, world_rank;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

        int error_code = 0;
        if (world_rank == 0) 
        {
            if (m1.empty() || m2.empty()) 
            {
                cerr << "Matrix should not be empty" << endl;
                error_code = 1;
            }
            else if (m1[0].size() != m2.size()) 
            {
                cerr << "Incompatible matrix size" << endl;
                error_code = 2;
            }
        }

        MPI_Bcast(&error_code, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (error_code != 0)
            return {};

        int sizes[4];
        if (world_rank == 0) 
        {
            sizes[0] = m1.size();
            sizes[1] = m1[0].size();
            sizes[2] = m2.size();
            sizes[3] = m2[0].size();
        }
        MPI_Bcast(sizes, 4, MPI_INT, 0, MPI_COMM_WORLD);
        const int rows_1 = sizes[0];
        const int cols_1 = sizes[1];
        const int rows_2 = sizes[2];
        const int cols_2 = sizes[3];

        vector<vector<float>> m2_local(rows_2, vector<float>(cols_2));
        if (world_rank == 0) 
        {
            m2_local = m2;
        }
        for (int i = 0; i < rows_2; ++i) 
        {
            MPI_Bcast(m2_local[i].data(), cols_2, MPI_FLOAT, 0, MPI_COMM_WORLD);
        }

        vector<vector<float>> local_m1;
        if (world_rank == 0) 
        {
            vector<int> counts(world_size), displs(world_size);
            int rows_per_process = rows_1 / world_size;
            int remainder = rows_1 % world_size;

            vector<float> send_buffer;
            send_buffer.reserve(rows_1 * cols_1);
            for (const auto& row : m1) {
                send_buffer.insert(send_buffer.end(), row.begin(), row.end());
            }

            for (int i = 0; i < world_size; ++i) 
            {
                counts[i] = rows_per_process * cols_1;
                if(i < remainder) 
                    counts[i] += cols_1;
                if (i == 0)
                    displs[i] = 0;
                else
                    displs[i] = displs[i - 1] + counts[i - 1];
            }

            int my_count = counts[0];
            vector<float> recv_buffer(my_count);
            MPI_Scatterv(send_buffer.data(), counts.data(), displs.data(), MPI_FLOAT,
                recv_buffer.data(), my_count, MPI_FLOAT, 0, MPI_COMM_WORLD);

            int my_rows = counts[0] / cols_1;
            local_m1.resize(my_rows, vector<float>(cols_1));
            for (int i = 0; i < my_rows; ++i) 
            {
                copy(recv_buffer.begin() + i * cols_1, recv_buffer.begin() + (i + 1) * cols_1, local_m1[i].begin());
            }
        }
        else 
        {
            int rows_per_process = rows_1 / world_size;
            int remainder = rows_1 % world_size;
            int my_rows = rows_per_process + (world_rank < remainder ? 1 : 0);
            int my_count = my_rows * cols_1;

            vector<float> recv_buffer(my_count);
            MPI_Scatterv(nullptr, nullptr, nullptr, MPI_FLOAT,
                recv_buffer.data(), my_count, MPI_FLOAT, 0, MPI_COMM_WORLD);

            local_m1.resize(my_rows, vector<float>(cols_1));
            for (int i = 0; i < my_rows; ++i) 
            {
                copy(recv_buffer.begin() + i * cols_1, recv_buffer.begin() + (i + 1) * cols_1, local_m1[i].begin());
            }
        }

        vector<vector<float>> local_result(local_m1.size(), vector<float>(cols_2, 0));
        for (size_t i = 0; i < local_m1.size(); ++i) 
        {
            for (int k = 0; k < rows_2; ++k) 
            {
                float temp = local_m1[i][k];
                for (int j = 0; j < cols_2; ++j) 
                {
                    local_result[i][j] += temp * m2_local[k][j];
                }
            }
        }

        vector<vector<float>> res;
        if (world_rank == 0) 
        {
            res.resize(rows_1, vector<float>(cols_2));
        }

        vector<float> send_buffer;
        send_buffer.reserve(local_result.size() * cols_2);
        for (const auto& row : local_result) 
        {
            send_buffer.insert(send_buffer.end(), row.begin(), row.end());
        }

        if (world_rank == 0) 
        {
            vector<int> counts(world_size), displs(world_size);
            int rows_per_process = rows_1 / world_size;
            int remainder = rows_1 % world_size;

            for (int i = 0; i < world_size; ++i) 
            {
                counts[i] = (rows_per_process + (i < remainder ? 1 : 0)) * cols_2;
                displs[i] = (i == 0) ? 0 : displs[i - 1] + counts[i - 1];
            }

            vector<float> recv_buffer(rows_1 * cols_2);
            MPI_Gatherv(send_buffer.data(), send_buffer.size(), MPI_FLOAT,
                recv_buffer.data(), counts.data(), displs.data(), MPI_FLOAT,
                0, MPI_COMM_WORLD);

            for (int i = 0; i < rows_1; ++i) 
            {
                copy(recv_buffer.begin() + i * cols_2, recv_buffer.begin() + (i + 1) * cols_2, res[i].begin());
            }
        }
        else 
        {
            MPI_Gatherv(send_buffer.data(), send_buffer.size(), MPI_FLOAT,
                nullptr, nullptr, nullptr, MPI_FLOAT,
                0, MPI_COMM_WORLD);
        }

        return res;
    }
};