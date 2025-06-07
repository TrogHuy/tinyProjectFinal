#include "Matrix.h"
#include "Vector.h"
#include <cassert>
#include <algorithm>
#include <iostream>
using namespace std;

Matrix::Matrix(): mNumRows(0), mNumCols(0), mData(NULL) {}

// Constructor with parameters
Matrix::Matrix(int numRows, int numCols): mNumRows(numRows), mNumCols(numCols) {
	mData = new double*[numRows];
	for(int i = 0; i < numRows; i++) {
		mData[i] = new double[numCols];
		for(int j = 0; j < numCols; j++) {
			mData[i][j] = 0.0;
		}
	}
}

// Copy other matrix
Matrix::Matrix(const Matrix &other) {
	mNumRows = other.mNumRows;
	mNumCols = other.mNumCols;

	mData = new double*[mNumRows];
	for(int i = 0; i < mNumRows; i++) {
		mData[i] = new double[mNumCols];
		for(int j = 0; j < mNumCols; j++) {
			mData[i][j] = other.mData[i][j];
		}
	}
}

// Assignment operator
Matrix& Matrix::operator=(const Matrix &other) {
	if(this != &other) {
		for(int i = 0; i < mNumRows; i++) {
			delete[] mData[i];
		}
		delete[] mData;

		mNumRows = other.mNumRows; mNumCols = other.mNumCols;
		mData = new double * [mNumRows];
		for(int i = 0; i < mNumRows; i++) {
			mData[i] = new double[mNumCols];
			for(int j = 0; j < mNumCols; j++) {
				mData[i][j] = other.mData[i][j];
			}
		}
	}
	return *this;
}

// Get number of rows
int Matrix::getNumRows() const {
	return mNumRows;
}

// Get number of columns
int Matrix::getNumCols() const {
	return mNumCols;
}

// 1-based indexing
double& Matrix::operator()(int i, int j){
	assert(i > 0 && i <= mNumRows && j > 0 && j <= mNumCols);
	return mData[i-1][j-1];
}

// Constant 1-based indexing
const double& Matrix::operator()(int i, int j) const {
	assert(i > 0 && i <= mNumRows && j > 0 && j <= mNumCols);
	return mData[i-1][j-1];
}

// Add 2 matrices
Matrix Matrix::operator+(const Matrix& other) const {
	assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
	Matrix result(mNumRows, mNumCols);

	for(int i = 0; i < mNumRows; i++) {
		for(int j = 0; j < mNumCols; j++)
			result(i+1, j+1) = mData[i][j] + other.mData[i][j];
	}
	return result;
}

// Subtract 2 matrices
Matrix Matrix::operator-(const Matrix& other) const {
	assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
	Matrix result(mNumRows, mNumCols);

	for(int i = 0; i < mNumRows; i++) {
		for(int j = 0; j < mNumCols; j++)
			result(i+1, j+1) = mData[i][j] - other.mData[i][j];
	}
	return result;
}

// Multiply 2 matrices
Matrix Matrix::operator*(const Matrix& other) const {
	assert(mNumCols == other.mNumRows);

	Matrix result(mNumRows, other.mNumCols);

	for(int i = 0; i < mNumRows; i++) {
		for(int j = 0; j < other.mNumCols; j++) {
			for(int k = 0; k < mNumCols; k++) {
				result(i+1,j+1) += mData[i][k] * other.mData[k][j];
			}
		}
	}

	return result;
}

// Multiply matrix with scalar
Matrix Matrix::operator*(double scalar) const {
	Matrix result(mNumRows, mNumCols);

	for(int i = 0; i < mNumRows; i++) {
		for(int j = 0; j < mNumCols; j++) {
			result(i+1, j+1) = mData[i][j] * scalar;
		}
	}

	return result;
}

// Multiply matrix with vector
Vector Matrix::operator*(const Vector &vector) const {
	assert(mNumCols == vector.size());

	Vector result(mNumRows, 0.0);

	for(int i = 0; i < mNumRows; i++) {
		for(int j = 0; j < mNumCols; j++) {
			result[i] += mData[i][j] * vector[j];
		}
	}

	return result;
}

// Gaussian Elimination Determinant
double Matrix::Determinant() const {
	assert(mNumRows == mNumCols);
	Matrix temp(*this);
	double det = 1.0;

	for (int i = 0; i < mNumRows; ++i) {
        // Pivot check
        if (temp(i + 1, i + 1) == 0.0) {
            // Find row to swap
            for (int k = i + 1; k < mNumRows; ++k) {
                if (temp(k + 1, i + 1) != 0.0) {
                    for (int j = 1; j <= mNumCols; ++j)
                        swap(temp(i + 1, j), temp(k + 1, j));
                    det *= -1; // Row swap changes sign
                    break;
                }
            }
        }
        // Eliminate
        for (int k = i + 1; k < mNumRows; ++k) {
            double factor = temp(k + 1, i + 1) / temp(i + 1, i + 1);
            for (int j = i + 1; j <= mNumCols; ++j)
                temp(k + 1, j) -= factor * temp(i + 1, j);
        }

        det *= temp(i + 1, i + 1);
    }

    return det;
};

// Gauss-Jordan Inverse
Matrix Matrix::Inverse() const {
	assert(mNumRows == mNumCols);
	int n = mNumRows;
	Matrix A(*this);
	Matrix I(n, n);

	for(int i = 1; i <= n; i++) {
		I(i, i) = 1.0;
	}

	for (int i = 0; i < n; ++i) {
        double pivot = A(i + 1, i + 1);
        assert(pivot != 0);

        for (int j = 0; j < n; ++j) {
            A(i + 1, j + 1) /= pivot;
            I(i + 1, j + 1) /= pivot;
        }

        for (int k = 0; k < n; ++k) {
            if (k == i) continue;
            double factor = A(k + 1, i + 1);
            for (int j = 0; j < n; ++j) {
                A(k + 1, j + 1) -= factor * A(i + 1, j + 1);
                I(k + 1, j + 1) -= factor * I(i + 1, j + 1);
            }
        }
    }

    return I;
}

// Transpose Matrix
Matrix Matrix::Transpose() const {
	Matrix result(mNumCols, mNumRows);

	for(int i = 0; i < mNumRows; ++i) {
		for(int j = 0; j < mNumCols; ++j) {
			result(j+1, i+1) = mData[i][j];
		}
	}
	return result;
}

// Moore-Penrose pseudo inverse
Matrix Matrix::PseudoInverse() const {
	Matrix At = this->Transpose();                   // A^t
    Matrix AtA = At * (*this);                       // A^t * A
    Matrix AtA_inv = AtA.Inverse();                  // (A^t * A)^(-1)
    Matrix pseudo = AtA_inv * At;                    // (A^t * A)^(-1) * A^t
    return pseudo;
}

void Matrix::print() const {
	for(int i = 0; i < mNumRows; i++) {
		for(int j = 0; j < mNumCols; j++) {
			cout << mData[i][j] << " ";
		}
		cout << endl;
	}
}

// Destructor
Matrix::~Matrix()
{
	for(int i = 0; i < mNumRows; i++) {
		delete[] mData[i];
	}
	delete[] mData;
}
