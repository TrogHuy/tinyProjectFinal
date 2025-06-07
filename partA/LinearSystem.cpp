#include "LinearSystem.h"
#include <cassert>
#include <cmath>
using namespace std;

LinearSystem::LinearSystem(Matrix *A, Vector *b) {

	Init(A, b);
}

void LinearSystem::Init(Matrix *A, Vector *b) {
    mpA = A;
    mpb = b;
    mSize = A->getNumRows();
}
LinearSystem::~LinearSystem() {
}

Vector LinearSystem::Solve() const {
	Matrix A(*mpA);
	Vector b(*mpb);
	Vector x(mSize); // result

	 for (int i = 0; i < mSize; ++i) {
        // Pivoting (optional for now)
        assert(A(i + 1, i + 1) != 0.0);  // prevent divide-by-zero

        for (int k = i + 1; k < mSize; ++k) {
            double factor = A(k + 1, i + 1) / A(i + 1, i + 1);
            for (int j = i + 1; j <= mSize; ++j)
                A(k + 1, j) -= factor * A(i + 1, j);
            b[k] -= factor * b[i];
        }
    }

    // Back-substitution
    for (int i = mSize - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < mSize; ++j)
            sum += A(i + 1, j + 1) * x[j];

        x[i] = (b[i] - sum) / A(i + 1, i + 1);
    }

    return x;
}

PosSymLinSystem::PosSymLinSystem(Matrix *A, Vector *b): LinearSystem(A, b) {
	int n = A->getNumRows();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            assert((*A)(i, j) == (*A)(j, i));
}

double DotProduct(const Vector& a, const Vector& b) {
    assert(a.size() == b.size());
    double sum = 0.0;
    for (int i = 0; i < a.size(); ++i)
        sum += a[i] * b[i];
    return sum;
}

Vector PosSymLinSystem::Solve() const {
    int n = mpb->size();
    Vector x(n, 0.0);               // Initial guess x0 = 0
    Vector r = *mpb;                // Initial residual r0 = b - A·x0 = b
    Vector p = r;                   // Initial direction
    Vector Ap(n);
    double rs_old = DotProduct(r, r);

    for (int k = 0; k < n; ++k) {
        Ap = (*mpA) * p;            // A·pk
        double alpha = rs_old / DotProduct(p, Ap);
        for (int i = 0; i < n; ++i) {
            x[i] += alpha * p[i];
            r[i] -= alpha * Ap[i];
        }
        double rs_new = DotProduct(r, r);
        if (sqrt(rs_new) < 1e-10) break; // convergence
        for (int i = 0; i < n; ++i)
            p[i] = r[i] + (rs_new / rs_old) * p[i];
        rs_old = rs_new;
    }

    return x;
}
