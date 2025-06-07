#ifndef LINEARSYSTEM_H
#define LINEARSYSTEM_H
#include "Vector.h"
#include "Matrix.h"
#include <cassert>

class LinearSystem
{
	private:
		LinearSystem();
		LinearSystem(const LinearSystem&);
		LinearSystem& operator=(const LinearSystem&);

	public:
		LinearSystem(Matrix *A, Vector *b);
		virtual ~LinearSystem();
		virtual Vector Solve() const;

	protected:
		void Init(Matrix *A, Vector *b);
		int mSize;
		Vector *mpb;
		Matrix *mpA;
};

class PosSymLinSystem: public LinearSystem {
	public:
		PosSymLinSystem(Matrix *A, Vector *b);
		virtual Vector Solve() const;
};

#endif
