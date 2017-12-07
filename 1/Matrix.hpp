#pragma once
#include <vector>

using namespace std;

class Matrix {
  public:
  vector<vector<double> > data;

  Matrix(const char* sourceFilePath);
  Matrix(const Matrix& mat);
  Matrix(vector<vector<double> > src);
  Matrix(int heigth, int width);
  void saveToFile(const char* destFilePath);

  vector<double>& operator[](int index);

  Matrix operator+(const Matrix& add);
  Matrix operator+(double add);
  Matrix operator-(const Matrix& sub);
  Matrix operator-(double sub);
  Matrix operator/(double sub);
  Matrix operator*(const Matrix& multi);
  Matrix operator*(double multi);
  Matrix operator!();
  bool operator==(const Matrix& cmp);
  void operator+=(const Matrix& src);
  void operator+=(double src);
  void operator*=(const Matrix& src);
  void operator*=(double src);
  void operator/=(double src);
  void operator-=(const Matrix& src);
  void operator-=(double src);
  Matrix& operator=(const Matrix& src);

  void LU();
  Matrix LUforward(Matrix src);
  Matrix LUbackward(Matrix src);
  Matrix LUP();
  static Matrix I(int);
  ~Matrix();
};

std::ostream& operator<<(std::ostream&, const Matrix&);
