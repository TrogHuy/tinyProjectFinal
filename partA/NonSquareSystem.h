#ifndef NONSQUARESYSTEM_H
#define NONSQUARESYSTEM_H
#include "LinearSystem.h"
#include "Matrix.h"
#include "Vector.h"
#include <cassert>

class NonSquareSystem: public LinearSystem {
	public:
		NonSquareSystem(Matrix *A, Vector *b);
		virtual Vector Solve() const override;
	private:
		int mRows, mCols;
};

#endif
