#include <vector>
#include <iostream>


using namespace std;


class MatrixMultiplicator {
public:
	static vector<vector<float>> multiply(vector<vector<float>> m1, vector<vector<float>> m2) {

		if (m1.empty() || m2.empty()) {
			cerr << "Matrix should not be empty" << endl;
			return {};
		}

		int rows_1 = m1.size();
		int cols_1 = m1[0].size();
		int rows_2 = m2.size();
		int cols_2 = m2[0].size();

		if (cols_1 != rows_2) {
			cerr << "Incompatible matrix size" << endl;
			return {};
		}

		vector<vector<float>> res(rows_1, vector<float>(cols_2, 0));

		for (int i = 0; i < rows_1; ++i) {
			for (int j = 0; j < cols_2; ++j) {
				for (int k = 0; k < rows_2; ++k) {
					res[i][j] += m1[i][k] * m2[k][j];
				}
			}
		}

		return res;
	}
};