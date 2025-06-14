#include "Evaluator.h"
#include <cmath>
#include <ctime>
#include <cassert>

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void shuffle(Vector &indices) {
    srand(time(0));
    for(int i = indices.size()-1; i > 0; i--) {
        int j = rand() % (i+1);
        swap(indices[i], indices[j]);
    }
}

void SplitTrainTest(const Matrix& A, const Vector& b,
                    Matrix& trainA, Vector& trainb,
                    Matrix& testA, Vector& testb,
                    double trainRatio) {
    int totalSamples = b.size();
    int numFeatures = A.getNumCols();
    int trainSize = static_cast<int>(totalSamples * trainRatio);
    int testSize = totalSamples - trainSize;

    // Shuffle indices
    Vector indices(totalSamples);
    for (int i = 0; i < totalSamples; ++i)
        indices[i] = i;
    shuffle(indices);

    // Allocate memory
    trainA = Matrix(trainSize, numFeatures);
    trainb = Vector(trainSize);
    testA = Matrix(testSize, numFeatures);
    testb = Vector(testSize);

    // Fill training set
    for (int i = 0; i < trainSize; ++i) {
        int idx = static_cast<int>(indices[i]);
        trainb[i] = b[idx];

        for (int j = 0; j < numFeatures; ++j) {
            trainA(i + 1, j + 1) = A(idx + 1, j + 1);
        }
    }

    // Fill test set
    for (int i = 0; i < testSize; ++i) {
        int idx = static_cast<int>(indices[trainSize + i]);
        testb[i] = b[idx];

        for (int j = 0; j < numFeatures; ++j) {
            testA(i + 1, j + 1) = A(idx + 1, j + 1);
        }
    }
}

double computeRMSE(const Vector& predicted, const Vector& actual) {
    assert(predicted.size() == actual.size());
    double sumSquaredError = 0.0;

    for(int i = 0; i < predicted.size(); i++) {
        double diff = predicted[i] - actual[i];
        sumSquaredError += diff * diff;
    }

    return sqrt(sumSquaredError / predicted.size());
}


void removeOutlierse(Matrix &A, Vector &b, double max_threshold) {
    int rows = A.getNumRows();
    int cols = A.getNumCols();

    int validCount = 0;
    for (int i = 0; i < b.size(); ++i) {
        if (b[i] <= max_threshold) {
            validCount++;
        }
    }

    Matrix filteredA(validCount, cols);
    Vector filteredb(validCount);

    int newRow = 1;  // 1-based indexing for Matrix
    for (int i = 0; i < b.size(); ++i) {
        if (b[i] <= max_threshold) {
            filteredb[newRow - 1] = b[i];
            for (int j = 1; j <= cols; ++j) {
                filteredA(newRow, j) = A(i + 1, j);
            }
            newRow++;
        }
    }
    A = filteredA;
    b = filteredb;
}
