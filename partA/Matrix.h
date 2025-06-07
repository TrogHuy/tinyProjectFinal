#ifndef MATRIX_H
#define MATRIX_H
#include "Vector.h"

class Matrix
{
	private:
		int mNumRows, mNumCols;
		double **mData;
	public:
		Matrix();
		// Parameterized constructor
		Matrix(int numRows, int numCols);
		
		// Copy
		Matrix& operator=(const Matrix &other);
		Matrix(const Matrix &other);
		
		int getNumRows() const; // Access number of rows
		int getNumCols() const; // Access number of columns
		
		double& operator()(int i, int j); // 1 based indexing
		const double& operator()(int i, int j) const;
		
		// Arithmetic operations
	    Matrix operator+(const Matrix& other) const;
	    Matrix operator-(const Matrix& other) const;
	    Matrix operator*(const Matrix& other) const;
	    Matrix operator*(double scalar) const;
	    Vector operator*(const Vector& vector) const;
	    
	    double Determinant() const;
	    
	    Matrix Inverse() const;
	    
	    Matrix PseudoInverse() const;
	    
	    Matrix Transpose() const;
	    
	    void print() const;
	    
		~Matrix();
};

#endif
