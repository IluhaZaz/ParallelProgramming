#include "matrixMultiply.cpp"
#include "IOtoFile.cpp"


void main() {
	auto res = FileHandler<int>::read_file("C:\\Users\\Acer\\Documents\\ParallelProgramming\\files\\input.txt");

	auto r = MatrixMultiplicator<int>::multiply(res.first, res.second);
}