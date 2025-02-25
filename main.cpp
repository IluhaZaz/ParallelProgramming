#include "matrixMultiply.cpp"
#include "IOtoFile.cpp"

#include <omp.h>


using namespace std;


void main() {
	auto input = FileHandler::read_input_file("C:\\Users\\Acer\\Documents\\ParallelProgramming\\files\\input.txt");

	double start = omp_get_wtime();
	auto r = MatrixMultiplicator::multiply(input.first, input.second);
	double end = omp_get_wtime();

	double duration = end - start;

	FileHandler::write_output_file(r, duration, "C:\\Users\\Acer\\Documents\\ParallelProgramming\\files\\output.txt");
}