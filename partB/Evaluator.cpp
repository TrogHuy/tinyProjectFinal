#include "Evaluator.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cassert>

void SplitTrainTest(const Matrix& A, const Vector& b,
                    Matrix& trainA, Vector& trainb,
                    Matrix& testA, Vector& testb,
                    double trainRatio) {
    int totalSamples = b.size();                   // Number of rows in A and size of b
    int numFeatures = A.getNumCols();              // Number of columns in A

    int trainSize = static_cast<int>(totalSamples * trainRatio);
    int testSize = totalSamples - trainSize;

    // Shuffle indices
    vector<int> indices(totalSamples);
    for (int i = 0; i < totalSamples; ++i)
        indices[i] = i;
    srand(time(0));
    random_shuffle(indices.begin(), indices.end());

    // Allocate memory
    trainA = Matrix(trainSize, numFeatures);
    trainb = Vector(trainSize);
    testA = Matrix(testSize, numFeatures);
    testb = Vector(testSize);

    // Fill training set
    for (int i = 0; i < trainSize; ++i) {
        int idx = indices[i];  // 0-based index
        trainb[i] = b[idx];  // Vector uses 0-based

        for (int j = 0; j < numFeatures; ++j) {
            // Matrix uses 1-based indexing
            trainA(i + 1, j + 1) = A(idx + 1, j + 1);
        }
    }

    // Fill test set
    for (int i = 0; i < testSize; ++i) {
        int idx = indices[trainSize + i];  // 0-based index
        testb[i] = b[idx];  // Vector uses 0-based

        for (int j = 0; j < numFeatures; ++j) {
            testA(i + 1, j + 1) = A(idx + 1, j + 1);  // Matrix uses 1-based
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
