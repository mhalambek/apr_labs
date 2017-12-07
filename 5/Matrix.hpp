#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix
{
public:
    Matrix(void);
    Matrix(int w, int h);
    Matrix(const char *fname);
    Matrix(const Matrix &A);
    ~Matrix(void);

    Matrix& operator=(const Matrix &A);
    bool operator==(const Matrix &A) const;

    Matrix& operator+=(const Matrix &A);
    Matrix& operator-=(const Matrix &A);
    Matrix& operator*=(double s);

    Matrix operator~(void) const;

    const double* operator[](int idx) const;
    double* operator[](int idx);

    void SetSize(int w, int h);

    int Width() const;
    int Height() const;

    static Matrix I(int n);
    static double EPS;

private:
    double *data;
    int n;
    int m;
};

std::ostream& operator<<(std::ostream &os, const Matrix &A);
std::istream& operator>>(std::istream &is, Matrix &A);

Matrix operator+(const Matrix &A, const Matrix &B);
Matrix operator-(const Matrix &A, const Matrix &B);
Matrix operator*(const Matrix &A, const Matrix &B);
Matrix operator*(const Matrix &A, double s);
Matrix operator*(double s, const Matrix &A);


Matrix ForwardSupstitution(const Matrix &L, const Matrix &b);
Matrix BackwardSupstitution(const Matrix &U, const Matrix &y);

//overwrites A with L and U, returns P
Matrix LUPDecomposition(Matrix &A, bool partitioning);

Matrix Inverse(const Matrix &A);

#endif // MATRIX_H
