#ifndef VECTOR_H
#define VECTOR_H

class Vector {
private:
    int mSize;
    double* mData;

public:
    Vector();
    Vector(int n);
    Vector(int n, double v);
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    // Unary operators
    Vector& operator-();
    Vector& operator++();      // Prefix ++
    Vector& operator++(int);   // Postfix ++
    Vector& operator--();      // Prefix --
    Vector& operator--(int);   // Postfix --

    // Indexing
    double& operator[](int index);
    const double& operator[](int index) const;

    double& operator()(int index);        // 1-based indexing
    const double& operator()(int index) const;

    // Arithmetic operations
    Vector operator+(const Vector& other) const;
    Vector operator+(double v) const;
    Vector operator-(const Vector& other) const;
    Vector operator-(double v) const;
    Vector operator*(const Vector& other) const;
    Vector operator*(double v) const;
    Vector operator/(const Vector& other) const;
    Vector operator/(double v) const;

    // Utilities
    void print() const;
    int size() const;

    ~Vector();
};

#endif

