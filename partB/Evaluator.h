#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Matrix.h"
#include "Vector.h"
#include <iostream>
using namespace std;

void SplitTrainTest(const Matrix &A, const Vector &b, Matrix &trainA, Vector &trainb, Matrix &testA, Vector &testb,
                    double trainRatio = 0.8);

double computeRMSE(const Vector &predicted, const Vector &actual);

void removeOutlierse(Matrix &A, Vector &b, double max_threshold=400);

#endif // EVALUATOR_H
