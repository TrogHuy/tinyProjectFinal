#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

void LoadDataFromFile(const string& filename, Matrix& A, Vector& b) {
    ifstream infile(filename);
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    // First read: count rows
    string line;
    int rowCount = 0;
    while (getline(file, line)) {
        if (!line.empty()) rowCount++;
    }

    int numFeatures = 6;
    A = Matrix(rowCount, numFeatures);
    b = Vector(rowCount);

    // Second read: read values
    file.clear(); // enable second read
    file.seekg(0, ios::beg); // move back to beginning of file

    int row = 1;
    int index = 0;

    while (getline(infile, line)) {
        if(line.empty()) continue;

        stringstream ss(line);
        string token;
        int col = 0;
        int value;

        // Skip vendor name and model name
        getline(ss, token, ',');  // vendor name
        getline(ss, token, ',');  // model name

        // Read 6 features
        for (int j = 1; j <= numFeatures; ++j) {
            getline(ss, token, ',');
            value = stoi(token);
            A(row, j) = value;
        }

        // PRP
        getline(ss, token, ',');  // PRP
        value = stoi(token);
        b[index] = value;

        row++;
        index++;
    }

    file.close();
}
