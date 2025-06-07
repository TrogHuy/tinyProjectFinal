#ifndef DATALOADER_H
#define DATALOADER_H
#include "Matrix.h"
#include "Vector.h"
#include <string>
using namespace std;

void LoadDataFromFile(const string& filename, Matrix& A, Vector& b);

#endif // DATALOADER_H
