#include "matrixMultiply.cpp"
#include "IOtoFile.cpp"


void main() {
	auto res = FileHandler::read_file("C:\\Users\\Acer\\Documents\\ParallelProgramming\\files\\input.txt");

	auto r = MatrixMultiplicator::multiply(res.first, res.second);

	FileHandler::write_file(r, "C:\\Users\\Acer\\Documents\\ParallelProgramming\\files\\output.txt");
}