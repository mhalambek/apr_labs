#include "Matrix.hpp"
#define epsilon 0.000001
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>

using namespace std;

Matrix::Matrix(int heigth, int width)
{
  data = vector<vector<double> >(heigth);
  for (auto& row : data) {
    row = vector<double>(width);
  }
}

Matrix::Matrix(const char* sourceFilePath)
{
  ifstream sourceFileStream(sourceFilePath);
  string line;
  while (getline(sourceFileStream, line)) {
    istringstream fin(line);
    data.push_back(vector<double>());
    double num;
    while (fin >> num) {
      data[data.size() - 1].push_back(num);
    }
  }

  sourceFileStream.close();
}

void Matrix::saveToFile(const char* destFilePath)
{
  ofstream destFile;
  destFile.open(destFilePath);

  for (auto row : data) {
    for (double t : row) {
      destFile << t << " ";
    }
    destFile << endl;
  }
  destFile.close();
}

vector<double>& Matrix::operator[](int index)
{
  return data[index];
}

Matrix::Matrix(const Matrix& mat)
{
  data = vector<vector<double> >(mat.data);
}

Matrix Matrix::operator+(const Matrix& add)
{
  Matrix ret(add);

  for (unsigned int i = 0; i < data.size(); ++i) {
    for (unsigned int j = 0; j < data[i].size(); ++j) {
      ret[i][j] += data[i][j];
    }
  }

  return ret;
}

Matrix Matrix::operator-(const Matrix& sub)
{
  Matrix ret(*this);

  for (unsigned int i = 0; i < data.size(); ++i) {
    for (unsigned int j = 0; j < data[i].size(); ++j) {
      ret[i][j] -= sub.data[i][j];
    }
  }

  return ret;
}

Matrix Matrix::operator/(double sub)
{
  Matrix ret(*this);

  for (unsigned int i = 0; i < data.size(); ++i) {
    for (unsigned int j = 0; j < data[i].size(); ++j) {
      ret[i][j] /= sub;
    }
  }

  return ret;
}

Matrix::Matrix(const vector<vector<double> > src)
{
  data = vector<vector<double> >(src);
}

Matrix Matrix::operator*(const Matrix& multi)
{
  // cout << "this: " << endl
  //      << (*this) << endl;
  Matrix ret(data.size(), multi.data[0].size());
  // cout << "ret : " << endl
  //      << ret;
  // cout << "multi:" << endl
  //      << multi << endl;
  for (unsigned int i = 0; i < data.size(); ++i) {
    for (unsigned int j = 0; j < multi.data[0].size(); ++j) {
      for (unsigned int k = 0; k < data[0].size(); ++k) {
        // cout << "k: " << k << endl;
        ret[i][j] += data[i][k] * multi.data[k][j];
      }
    }
  }
  // for (int row = 0; row < h; ++row)
  //   for (int col = 0; col < w; ++col)
  //     for (int i = 0; i < inner; ++i) {
  //       cout << "row: " << row << ", col: " << col << endl;
  //
  //       R[row][col] += data[row][i] * multi.data[i][col];
  //     }

  return ret;
}

Matrix Matrix::operator*(double multi)
{
  Matrix ret(*this);

  // for (unsigned int i = 0; i < ret.data.size(); ++i) {
  //   for (unsigned int j = 0; j < ret.data[i].size(); ++j) {
  //     ret.data[i][j] *= multi;
  //   }
  // }

  for (auto& row : ret.data) {
    for (double& d : row) {
      d *= multi;
    }
  }

  return ret;
}

Matrix Matrix::operator!()
{
  vector<vector<double> > src;
  for (unsigned int i = 0; i < data[0].size(); ++i) {
    src.push_back(vector<double>(data.size()));
  }

  for (unsigned int i = 0; i < this->data[0].size(); ++i) {
    for (unsigned int j = 0; j < this->data.size(); ++j) {
      src[i][j] = this->data[j][i];
    }
  }

  return Matrix(src);
}

void Matrix::operator+=(const Matrix& src)
{
  for (unsigned int i = 0; i < data.size(); ++i) {
    for (unsigned int j = 0; j < data[i].size(); ++j) {
      data[i][j] += src.data[i][j];
    }
  }
}

void Matrix::operator-=(const Matrix& src)
{
  for (unsigned int i = 0; i < data.size(); ++i) {
    for (unsigned int j = 0; j < data[i].size(); ++j) {
      data[i][j] -= src.data[i][j];
    }
  }
}

// void Matrix::operator*=(const Matrix& src)
// {
//   Matrix temp = (*this) * src;
//   data = vector<vector<double> >(temp.data);
// }

bool Matrix::operator==(const Matrix& cmp)
{
  for (unsigned int i = 0; i < data.size(); ++i) {
    for (unsigned int j = 0; j < data[i].size(); ++j) {
      if (fabs(data[i][j] - cmp.data[i][j]) > epsilon) {
        return false;
      }
    }
  }

  return true;
}

Matrix& Matrix::operator=(const Matrix& src)
{
  data = vector<vector<double> >(src.data);

  return *this;
}

Matrix Matrix::operator+(double add)
{
  Matrix ret(*this);

  for (unsigned int i = 0; i < ret.data.size(); ++i) {
    for (unsigned int j = 0; j < ret[i].size(); ++j) {
      ret[i][j] += add;
    }
  }

  return ret;
}

Matrix Matrix::operator-(double add)
{
  Matrix ret(*this);

  for (unsigned int i = 0; i < ret.data.size(); ++i) {
    for (unsigned int j = 0; j < ret[i].size(); ++j) {
      ret[i][j] -= add;
    }
  }

  return ret;
}

void Matrix::operator+=(double src)
{
  for (auto& row : data) {
    for (double& d : row) {
      d += src;
    }
  }
}

void Matrix::operator-=(double src)
{
  for (auto& row : data) {
    for (double& d : row) {
      d -= src;
    }
  }
}

void Matrix::operator*=(double src)
{
  for (auto& row : data) {
    for (double& d : row) {
      d *= src;
    }
  }
}

void Matrix::operator/=(double src)
{
  for (auto& row : data) {
    for (double& d : row) {
      d /= src;
    }
  }
}

/*
 *za i = 1 do n-1
     za j = i+1 do n
             A[j,i] /= A[i,i];
                     za k = i+1 do n
                                 A[j,k] -= A[j,i] * A[i,k];
 * */
void Matrix::LU()
{
  const int n = data.size();

  for (int i = 0; i < n; ++i) {
    if (fabs(data[i][i]) < epsilon) {
      cout << "LU decomp divide zero" << endl;
      break;
    }
    for (int j = i + 1; j < n; ++j) {
      data[j][i] /= data[i][i];
      for (int k = i + 1; k < n; ++k) {
        data[j][k] -= data[i][k] * data[j][i];
      }
    }
  }
}

/*
 *iza i = 1 do n-1 << endl;
     za j = i+1 do n
             b[j] -= A[j,i] * b[i];
 * */
Matrix Matrix::LUbackward(Matrix b)
{
  const int n = b.data.size();
  Matrix y(n, 1);
  // cout << "LUforward y:" << endl
  //      << y << endl;

  for (int i = n - 1; i > -1; --i) {
    y[i][0] = b[i][0];
    y[i][0] /= data[i][i];
    for (int j = i - 1; j > -1; --j) {
      b[j][0] -= data[j][i] * y[i][0];
    }
  }

  return y;
}

/*
 *za i = n do 1
     b[i] /= A[i,i];
         za j = 1 do i-1
                 b[j] -= A[j,i] * b[i];
 */
Matrix Matrix::LUforward(Matrix src)
{
  const unsigned int n = src.data.size();
  Matrix ret(n, 1);

  for (unsigned int i = 0; i < n; ++i) {
    // cout << "alive: " << i << endl;

    ret[i][0] = src[i][0];
    for (unsigned int j = i + 1; j < n; ++j) {
      src[j][0] -= ret[i][0] * data[j][i];
    }
  }

  return ret;
}

/*
 *za i = 1 do n
    P[i] = i;
za i = 1 do n-1
    pivot = i;
    za j = i+1 do n
        ako ( abs(A[P[j],i]) > abs(A[P[pivot],i) )
            pivot = j;
    zamijeni(P[i],P[pivot]);
    za j = i+1 do n
        A[P[j],i] /= A[P[i],i];
        za k = i+1 do n
            A[P[j],k] -= A[P[j],i] * A[P[i],k];
 * */
// Matrix Matrix::LUP()
Matrix Matrix::LUP()
{
  const int n = data.size();
  Matrix P = Matrix::I(n);

  for (int i = 0; i < n; ++i) {
    double maxv = -numeric_limits<double>::max();
    int maxidx;
    for (int j = i; j < n; ++j) {
      if (fabs(data[j][i]) > maxv) {
        maxv = data[j][i];
        maxidx = j;
      }
    }
    swap(data[i], data[maxidx]);
    swap(P.data[i], P.data[maxidx]);

    for (int j = i + 1; j < n; ++j) {
      data[j][i] /= data[i][i];
      for (int k = i + 1; k < n; ++k) {
        data[j][k] -= data[i][k] * data[j][i];
      }
    }

    // cout << "stpe lu" << endl
    //      << (*this) << endl;
  }
  // cout << "mat after lu: " << endl
  //      << (*this) << endl;
  // LU();
  // cout << "mat after lu: " << endl
  //      << (*this) << endl;

  return P;
}

Matrix Matrix::I(int n)
{
  Matrix ret(n, n);

  for (int i = 0; i < n; ++i) {
    ret.data[i][i] = 1;
  }

  return ret;
}

ostream& operator<<(ostream& os, const Matrix& obj)
{
  // os << obj.getXYZ() << obj.getABC() << '\n';
  for (auto row : obj.data) {
    for (double d : row) {
      os << d << " ";
    }
    os << endl;
  }

  return os;
}

Matrix::~Matrix()
{
  // delete data;
}
