#include "Matrix.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

double Matrix::EPS = 1e-6;

Matrix::Matrix(void)
    : data(nullptr)
    , n(0)
    , m(0)
{
}

Matrix::Matrix(int w, int h)
    : data(nullptr)
{
  SetSize(w, h);
}

Matrix::Matrix(const char* fname)
    : data(nullptr)
    , n(0)
    , m(0)
{
  ifstream ifs(fname);
  if (ifs.is_open())
    ifs >> *this;
  else {
    cout << "No Such file or directory: " + string(fname) << endl;
    exit(-1);
  }
}

Matrix::Matrix(const Matrix& A)
{
  n = A.Height();
  m = A.Width();
  data = new double[n * m];
  memcpy(data, A[0], n * m * sizeof(double));
}

Matrix::~Matrix()
{
  if (data != nullptr)
    delete[] data;
  n = m = 0;
}

Matrix& Matrix::operator=(const Matrix& A)
{
  if (this == &A)
    return *this; // handle self assignment

  if (data != nullptr)
    delete[] data;

  n = A.Height();
  m = A.Width();
  data = new double[n * m];
  memcpy(data, A[0], n * m * sizeof(double));

  return *this;
}

bool Matrix::operator==(const Matrix& A) const
{
  if (n != A.Height() || m != A.Width())
    return false;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (abs(A[i][j] - data[i * m + j]) > EPS)
        return false;

  return true;
}

Matrix& Matrix::operator+=(const Matrix& A)
{
  assert(n == A.Height() && m == A.Width());

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      data[i * m + j] += A[i][j];
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& A)
{
  assert(n == A.Height() && m == A.Width());

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      data[i * m + j] -= A[i][j];
  return *this;
}

Matrix& Matrix::operator*=(double s)
{
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      data[i * m + j] *= s;
  return *this;
}

Matrix Matrix::operator~() const
{
  Matrix A(n, m);

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      A[j][i] = data[i * m + j];

  return A;
}

const double* Matrix::operator[](int idx) const
{
  assert(idx < n);
  return data + m * idx;
}

double* Matrix::operator[](int idx)
{
  assert(idx < n);
  return data + m * idx;
}

void Matrix::SetSize(int w, int h)
{
  n = h;
  m = w;
  if (data != nullptr)
    delete[] data;
  data = new double[n * m];
  fill(data, data + n * m, 0.0);
}

int Matrix::Width() const
{
  return m;
}

int Matrix::Height() const
{
  return n;
}

Matrix Matrix::I(int n)
{
  Matrix R(n, n);
  for (int i = 0; i < n; ++i)
    R[i][i] = 1.0;
  return R;
}

ostream& operator<<(ostream& os, const Matrix& A)
{
  for (int i = 0; i < A.Height(); ++i) {
    for (int j = 0; j < A.Width(); ++j)
      os << A[i][j] << " ";
    os << endl;
  }

  return os;
}

istream& operator>>(istream& is, Matrix& A)
{
  vector<double> values;
  int h = 0;
  for (string line; getline(is, line);) {
    ++h;
    istringstream iss(line);
    double v;
    while (iss >> v)
      values.push_back(v);
  }

  A.SetSize(values.size() / h, h);
  memcpy(A[0], values.data(), values.size() * sizeof(double));

  return is;
}

Matrix operator+(const Matrix& A, const Matrix& B)
{
  Matrix R(A);
  return R += B;
}

Matrix operator-(const Matrix& A, const Matrix& B)
{
  Matrix R(A);
  return R -= B;
}

Matrix operator*(const Matrix& A, const Matrix& B)
{
  const int h = A.Height();
  const int w = B.Width();
  const int inner = A.Width();

  assert(inner == B.Height());

  Matrix R(w, h);

  for (int row = 0; row < h; ++row)
    for (int col = 0; col < w; ++col)
      for (int i = 0; i < inner; ++i)
        R[row][col] += A[row][i] * B[i][col];

  return R;
}

Matrix operator*(const Matrix& A, double s)
{
  Matrix R(A);
  return R *= s;
}

Matrix operator*(double s, const Matrix& A)
{
  Matrix R(A);
  return R *= s;
}

Matrix ForwardSupstitution(const Matrix& L, const Matrix& b)
{
  const int n = L.Height();
  Matrix y(n, 1);

  for (int i = 0; i < n; ++i) {
    y[0][i] = b[0][i];
    for (int j = 0; j < i; ++j)
      y[0][i] -= L[i][j] * y[0][j];
  }

  return y;
}

Matrix BackwardSupstitution(const Matrix& U, const Matrix& b)
{
  const int n = U.Height();
  Matrix x(n, 1);

  for (int i = n - 1; i >= 0; --i) {
    x[0][i] = b[0][i];
    for (int j = i + 1; j < n; ++j)
      x[0][i] -= U[i][j] * x[0][j];

    x[0][i] /= U[i][i];
  }

  return x;
}

void LUDecomposition(Matrix& A)
{
  const int n = A.Width();

  for (int k = 0; k < n - 1; ++k) {
    assert(abs(A[k][k]) > Matrix::EPS);
    for (int i = k + 1; i < n; ++i) {
      A[i][k] /= A[k][k];
      for (int j = k + 1; j < n; ++j)
        A[i][j] -= A[i][k] * A[k][j];
    }
  }
}

Matrix LUPDecomposition(Matrix& A, bool partitioning)
{
  const int n = A.Width();
  Matrix P = Matrix::I(n);

  if (partitioning) {
    for (int i = 0; i < n; ++i) {
      double maxv = -numeric_limits<double>::max();
      int maxidx;
      for (int j = i; j < n; ++j) {
        if (A[i][j] > maxv) {
          maxv = A[i][j];
          maxidx = j;
        }
      }

      for (int j = 0; j < n; ++j) {
        swap(A[j][i], A[j][maxidx]);
        swap(P[j][i], P[j][maxidx]);
      }
    }
  }

  LUDecomposition(A);

  return P;
}

Matrix Inverse(const Matrix& A)
{
  Matrix LU(A);
  const Matrix P = LUPDecomposition(LU, true);

  const int N = A.Width();
  Matrix inv(N, N);
  for (int i = 0; i < N; ++i) {
    Matrix e(N, 1);
    e[0][i] = 1.0;

    const Matrix y = ForwardSupstitution(LU, P * ~e);
    const Matrix x = BackwardSupstitution(LU, y);

    for (int j = 0; j < N; ++j)
      inv[j][i] = x[0][j];
  }

  return inv;
}
