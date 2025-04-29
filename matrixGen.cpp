#include <iostream>
#include <vector>
#include <random>

using namespace std;


vector<vector<float> > generateRandomMatrix(int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0, 1.0);
    
    vector<vector<float> > res(size, vector<float>(size));
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            res[i][j] = dis(gen);
        }
    }
    
    return res;
}


void printMatrix(const vector<vector<float> >& matrix) {
    for (const auto& row : matrix) {
        for (float val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}