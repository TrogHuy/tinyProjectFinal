#include "Vector.h"
#include <cassert>
#include <iostream>
using namespace std;

Vector::Vector(): mSize(0), mData(NULL) {}

Vector::Vector(int n) : mSize(n), mData(new double[n]) {
    for (int i = 0; i < n; i++)
        mData[i] = 0.0;
}

Vector::Vector(int n, double v) : mSize(n), mData(new double[n]) {
    for (int i = 0; i < n; i++)
        mData[i] = v;
}

Vector::Vector(const Vector& other) : mSize(other.mSize), mData(new double[other.mSize]) {
    for (int i = 0; i < mSize; i++)
        mData[i] = other.mData[i];
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] mData;
        mSize = other.mSize;
        mData = new double[mSize];
        for (int i = 0; i < mSize; i++)
            mData[i] = other.mData[i];
    }
    return *this;
}

Vector& Vector::operator-() {
    for (int i = 0; i < mSize; i++)
        mData[i] = -mData[i];
    return *this;
}

Vector& Vector::operator++() {
    for (int i = 0; i < mSize; i++)
        ++mData[i];
    return *this;
}

Vector& Vector::operator++(int) {
    Vector temp(*this);
    ++(*this);
    return *this;
}

Vector& Vector::operator--() {
    for (int i = 0; i < mSize; i++)
        --mData[i];
    return *this;
}

Vector& Vector::operator--(int) {
    Vector temp(*this);
    --(*this);
    return *this;
}

double& Vector::operator[](int index) {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

const double& Vector::operator[](int index) const {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

double& Vector::operator()(int index) {
    assert(index > 0 && index <= mSize);
    return mData[index - 1];
}

const double& Vector::operator()(int index) const {
    assert(index > 0 && index <= mSize);
    return mData[index - 1];
}

Vector Vector::operator+(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; i++)
        result[i] = mData[i] + other.mData[i];
    return result;
}

Vector Vector::operator+(double v) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++)
        result[i] = mData[i] + v;
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; i++)
        result[i] = mData[i] - other.mData[i];
    return result;
}

Vector Vector::operator-(double v) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++)
        result[i] = mData[i] - v;
    return result;
}

Vector Vector::operator*(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; i++)
        result[i] = mData[i] * other.mData[i];
    return result;
}

Vector Vector::operator*(double v) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++)
        result[i] = mData[i] * v;
    return result;
}

Vector Vector::operator/(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; i++)
        result[i] = mData[i] / other.mData[i];
    return result;
}

Vector Vector::operator/(double v) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++)
        result[i] = mData[i] / v;
    return result;
}

void Vector::print() const {
    for (int i = 0; i < mSize; i++)
        cout << mData[i] << " ";
    cout << endl;
}

int Vector::size() const {
    return mSize;
}

Vector::~Vector() {
    delete[] mData;
}

