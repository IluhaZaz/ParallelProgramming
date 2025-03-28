#include "matrixMultiply.cpp"
#include "IOtoFile.cpp"

#include <omp.h>


using namespace std;


void main() {
	int num_procs = omp_get_num_procs();
	omp_set_num_threads(num_procs);
	std::cout << "Available processors: " << num_procs << std::endl;
	
	auto input = FileHandler::read_input_file("C:\\Users\\Acer\\Documents\\ParallelProgramming\\files\\input.txt");

	double start = omp_get_wtime();
	auto r = MatrixMultiplicator::multiply(input.first, input.second);
	double end = omp_get_wtime();

	double duration = end - start;

	FileHandler::write_output_file(r, duration, "C:\\Users\\Acer\\Documents\\ParallelProgramming\\files\\output.txt");
}