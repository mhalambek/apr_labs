#include "Utils.hpp"
#include <fstream>

using namespace std;

bool operator<=(const Point& p1, const Point& p2)
{
  for (int i = 0; i < p1.size(); ++i)
    if (p1[i] > p2[i])
      return false;
  return true;
}

bool operator<(const Point& p1, const Point& p2)
{
  for (int i = 0; i < p1.size(); ++i)
    if (p1[i] >= p2[i])
      return false;
  return true;
}

Point operator*(double x, const Point& p)
{
  Point ret;
  for (double pi : p)
    ret.push_back(x * pi);
  return ret;
}

Point operator*(const Matrix& A, const Point& p)
{
  Point ret;
  const int w = A.Width();
  const int h = A.Height();
  for (int i = 0; i < h; ++i) {
    double s = 0.0;
    for (int j = 0; j < w; ++j)
      s += A[i][j] * p[j];
    ret.push_back(s);
  }
  return ret;
}

Point operator-(const Point& p1, const Point& p2)
{
  Point ret;
  for (int i = 0; i < p1.size(); ++i)
    ret.push_back(p1[i] - p2[i]);
  return ret;
}

Point operator+(const Point& p1, const Point& p2)
{
  Point ret;
  for (int i = 0; i < p1.size(); ++i)
    ret.push_back(p1[i] + p2[i]);
  return ret;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
  for (double pi : p)
    os << pi << " ";
  return os;
}

double norm(const Point& p)
{
  double ret = 0.0;
  for (double pi : p)
    ret += pi * pi;
  return sqrt(ret);
}

double dist(const Point& p1, const Point& p2)
{
  double ret = 0.0;
  for (int i = 0; i < p1.size(); ++i)
    ret += (p1[i] - p2[i]) * (p1[i] - p2[i]);
  return sqrt(ret);
}

NumIntInfo::NumIntInfo(double T, double tmax)
    : T(T)
    , tmax(tmax)
{
}

void NumIntInfo::ToFile(const char* fname) const
{
  ofstream outfile(fname);
  outfile << T << endl;
  outfile << tmax << endl;
  for (double pi : p)
    outfile << pi << endl;
}

Point MovedPoint(const Point& C, double factor, const Point& X)
{
  const int N = C.size();
  Point Xn(N);
  for (int i = 0; i < N; ++i)
    Xn[i] = C[i] + factor * (C[i] - X[i]);

  return Xn;
}
