#include "matrixMultiply.cpp"
#include "IOtoFile.cpp"

#include <chrono>


using namespace std;


void main() {
	auto input = FileHandler::read_input_file("C:\\Users\\Acer\\Documents\\ParallelProgramming\\files\\input.txt");

	auto start = chrono::high_resolution_clock::now();
	auto r = MatrixMultiplicator::multiply(input.first, input.second);
	auto end = chrono::high_resolution_clock::now();

	double duration = chrono::duration<double>(end - start).count();

	FileHandler::write_output_file(r, duration, "C:\\Users\\Acer\\Documents\\ParallelProgramming\\files\\output.txt");
}