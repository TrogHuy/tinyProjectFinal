#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
using namespace std;

void LoadDataFromFile(const std::string& filename, Matrix& A, Vector& b) {
    ifstream infile(filename);
    string line;
    vector<vector<double>> feature_rows;
    vector<double> target_values;

    while (getline(infile, line)) {
        stringstream ss(line);
        string token;
        vector<double> row;

        // Skip vendor name and model name
        getline(ss, token, ',');  // vendor name
        getline(ss, token, ',');  // model name

        // 6 features columns
        for (int i = 0; i < 6; ++i) {
            getline(ss, token, ',');
            row.push_back(stod(token));
        }

        // PRP
        getline(ss, token, ',');  // PRP
        target_values.push_back(stod(token));

        // Add features to matrix row list
        feature_rows.push_back(row);
    }

    int numRows = feature_rows.size();
    int numCols = 6;

    A = Matrix(numRows, numCols);
    b = Vector(numRows);

    for (int i = 0; i < numRows; ++i) {
        b[i] = target_values[i];
        for (int j = 0; j < numCols; ++j) {
            A(i + 1, j + 1) = feature_rows[i][j];
        }
    }
}
