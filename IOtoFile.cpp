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
            vector<vector<T>> m1;
            vector<vector<T>> m2;

            string line;
            int num;

            while (getline(input_file, line) && line != "") {
                vector<T> curr_row;

                stringstream ss(line);
                while (ss >> num) {
                    curr_row.push_back(num);
                }

                m1.push_back(curr_row);
            }

            res.first = m1;

            while (getline(input_file, line)) {
                vector<T> curr_row;

                stringstream ss(line);
                while (ss >> num) {
                    curr_row.push_back(num);
                }

                m2.push_back(curr_row);
            }

            res.second = m2;

            input_file.close();
            return res;
        }
	}
};