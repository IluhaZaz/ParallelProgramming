#include <mpi.h>
#include <cstdlib>
#include <vector>
#include <utility>
#include <chrono>
#include <iostream>

#include "matrixGen.cpp"
#include "matrixMultiply.cpp"

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size = atoi(argv[1]);
    cout << size << endl;

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    pair<vector<vector<float> >, vector<vector<float> > > input;
    if (world_rank == 0) {
        input.first = generateRandomMatrix(size);
        input.second = generateRandomMatrix(size);
    }

    auto start = chrono::high_resolution_clock::now();
    auto r = MatrixMultiplicator::multiply(input.first, input.second);
    auto end = chrono::high_resolution_clock::now();

    if (world_rank == 0) {
        double duration = chrono::duration<double>(end - start).count();
        cout << duration << endl;
    }

    MPI_Finalize();
    return 0;
}