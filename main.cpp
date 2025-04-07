#include "matrixMultiply.cpp"
#include "IOtoFile.cpp"
#include <chrono>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    pair<vector<vector<float>>, vector<vector<float>>> input;
    if (world_rank == 0) {
        input = FileHandler::read_input_file("C:\\Users\\Acer\\Documents\\ParallelProgramming\\files\\input.txt");
    }

    auto start = chrono::high_resolution_clock::now();
    auto r = MatrixMultiplicator::multiply(input.first, input.second);
    auto end = chrono::high_resolution_clock::now();

    if (world_rank == 0) {
        double duration = chrono::duration<double>(end - start).count();
        FileHandler::write_output_file(r, duration, "C:\\Users\\Acer\\Documents\\ParallelProgramming\\files\\output.txt");
    }

    MPI_Finalize();
    return 0;
}