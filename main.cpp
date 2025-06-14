#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "LinearSystem.h"
#include "NonSquareSystem.h"
#include "DataLoader.h"
#include "Evaluator.h"
using namespace std;

int main() {
    // ----------------- Test Matrix and Vector -----------------
    cout << "Testing Vector and Matrix classes:\n";
    Vector v(3);
    v[0] = 1.0; v[1] = 2.0; v[2] = 3.0;
    v.print();

    Matrix M(3, 3);
    for (int i = 1; i <= 3; ++i)
        for (int j = 1; j <= 3; ++j)
            M(i, j) = i * j;
    M.print();

    // ----------------- Solve Linear System -----------------
    cout << "\nSolving Linear System using Gaussian Elimination:\n";
    Matrix A(3, 3);
    A(1,1) = 2; A(1,2) = -1; A(1,3) = 0;
    A(2,1) = -1; A(2,2) = 2; A(2,3) = -1;
    A(3,1) = 0; A(3,2) = -1; A(3,3) = 2;
    Vector b(3);
    b[0] = 1; b[1] = 0; b[2] = 1;
    LinearSystem ls(&A, &b);
    Vector x = ls.Solve();
    x.print();

    // ----------------- Solve Positive Symmetric System -----------------
    cout << "\nSolving Positive Definite System using Conjugate Gradient:\n";
    Matrix P(3, 3);
    P(1,1) = 4; P(1,2) = 1; P(1,3) = 1;
    P(2,1) = 1; P(2,2) = 3; P(2,3) = 0;
    P(3,1) = 1; P(3,2) = 0; P(3,3) = 2;
    Vector p_rhs(3);
    p_rhs[0] = 6; p_rhs[1] = 5; p_rhs[2] = 4;
    PosSymLinSystem psys(&P, &p_rhs);
    Vector px = psys.Solve();
    px.print();

    // ----------------- Solve Non-Square System -----------------
    cout << "\nSolving Overdetermined System using Pseudo-Inverse:\n";
    Matrix B(5, 3);
    B(1,1)=1; B(1,2)=2; B(1,3)=3;
    B(2,1)=2; B(2,2)=3; B(2,3)=4;
    B(3,1)=3; B(3,2)=4; B(3,3)=5;
    B(4,1)=4; B(4,2)=5; B(4,3)=6;
    B(5,1)=5; B(5,2)=6; B(5,3)=7;
    Vector c(5);
    c[0] = 1; c[1] = 2; c[2] = 3; c[3] = 4; c[4] = 5;
    NonSquareSystem nsys(&B, &c);
    Vector nx = nsys.Solve();
    nx.print();

    // ----------------- Load UCI Dataset and Evaluate -----------------
    cout << "\nLoading UCI CPU dataset and evaluating linear regression model:\n";
    Matrix E;
    Vector e;
    LoadDataFromFile("machine.data", E, e);

    Matrix trainE, testE;
    Vector traine, teste;
    SplitTrainTest(E, e, trainE, traine, testE, teste);

    NonSquareSystem model(&trainE, &traine);
    Vector coeff = model.Solve();

    cout << "-----------------------Before Removing Outlierse-------------------------\n";
    // Predict on training set
    Vector trainPredicted_before = trainE * coeff;
    double trainRMSE_before = computeRMSE(trainPredicted_before, traine);
    cout << "\nRMSE on training set before removing outlierse: " << trainRMSE_before << endl;

    // Predict on test set
    Vector testPredicted_before = testE * coeff;
    double testRMSE_before = computeRMSE(testPredicted_before, teste);
    cout << "RMSE on test set before removing outlierse: " << testRMSE_before << endl;
    cout << endl;

    cout << "----------------------After Removing Outlierse---------------------------\n";

    removeOutlierse(E, e);
    SplitTrainTest(E, e, trainE, traine, testE, teste);

    NonSquareSystem model_after(&trainE, &traine);
    Vector coeff_after = model_after.Solve();

    Vector trainPredicted_after = trainE * coeff_after;
    double trainRMSE_after = computeRMSE(trainPredicted_after, traine);
    cout << "\nRMSE on training set after removing outlierse: " << trainRMSE_after << endl;

    Vector testPredicted_after = testE * coeff_after;
    double testRMSE_after = computeRMSE(testPredicted_after, teste);
    cout << "RMSE on test set after removing outlierse: " << testRMSE_after << endl;
    return 0;
}
