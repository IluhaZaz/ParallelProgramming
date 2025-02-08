#include <vector>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

template <typename T>
class FileHandler {
public:
	static pair<vector<vector<T>>, vector<vector<T>>> read_file(string path) {
		ifstream input_file(path);

        if (input_file.is_open()) {

            pair<vector<vector<T>>, vector<vector<T>>> res;

            res.first = read_matrix(input_file);
            res.second = read_matrix(input_file);

            input_file.close();
            return res;
        }
	}

    static vector<vector<T>> read_matrix(ifstream& input_file) {
        vector<vector<T>> matrix;

        string line;
        int num;

        while (getline(input_file, line) && line != "") {
            vector<T> curr_row;

            stringstream ss(line);
            while (ss >> num) {
                curr_row.push_back(num);
            }

            matrix.push_back(curr_row);
        }

        return matrix;
    }

    static void write_file(vector<vector<T>>& matrix, string path) {
        ofstream output_file(path);

        if (output_file.is_open()) {
            for (int i = 0; i < matrix.size(); ++i) {
                for (int j = 0; j < matrix[0].size(); ++j) {
                    output_file << matrix[i][j] << ' ';
                }
                output_file << '\n';
            }
        }

        output_file.close();
    }
};