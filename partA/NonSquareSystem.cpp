#include "NONSQUARESYSTEM.h"
#include <cassert>
#include <cmath>

NonSquareSystem::NonSquareSystem(Matrix* A, Vector* b): LinearSystem(A, b)
{
	assert(A->getNumRows() != A->getNumCols());
    assert(A->getNumRows() == b->size());

    Init(A, b);
    mRows = A->getNumRows();
    mCols = A->getNumCols();
}

// Solve using Moore-Penrose Pseudo-Inverse
Vector NonSquareSystem::Solve() const {
	Matrix At = mpA->Transpose();
    Vector result(mCols, 0.0);

    if (mRows >= mCols) {
        // Over-determined system: x = (At * A)^(-1) At * b
        Matrix AtA = At * (*mpA);
        Matrix AtAInv = AtA.Inverse();
        Matrix pseudoInv = AtAInv * At;
        result = pseudoInv * (*mpb);
    } else {
        // Under-determined system: x = At (A At)^(-1) b
        Matrix AAt = (*mpA) * At;
        Matrix AAtInv = AAt.Inverse();
        Matrix pseudoInv = At * AAtInv;
        result = pseudoInv * (*mpb);
    }

    return result;
}
