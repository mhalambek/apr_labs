#pragma once
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

// double RosenbrockBanana(double x, double y)
double f1(vector<double> x)
{

  return 100 * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]) + (1 - x[0]) * (1 - x[0]);
}

double f2(vector<double> x)
{
  double x1 = x[0], x2 = x[1];

  return (x1 - 4) * (x1 - 4) + 4 * (x2 - 2) * (x2 - 2);
}

double f3(vector<double> x)
{
  double ret = 0;

  for (unsigned int i = 0; i < x.size(); ++i) {
    ret += (x[i] - i - 1) * (x[i] - i - 1);
  }

  return ret;
}

// double f3(double x1, double x2)
// {
//   vector<double> temp;
//   temp.push_back(x1);
//   temp.push_back(x2);
//
//   return f3(temp);
// }

double f4(vector<double> x)
{
  double x1 = x[0], x2 = x[1];
  return abs((x1 + x2) * (x1 - x2)) + sqrt(x1 * x1 + x2 * x2);
}

double Schaffer(vector<double> x)
{
  double sumOfSquares = 0;
  for (auto t : x) {
    sumOfSquares += t * t;
  }

  return 0.5 + ((sin(sqrt(sumOfSquares)) * sin(sqrt(sumOfSquares))) - 0.5) / (1 + 0.001 * sumOfSquares);
}
double f6(double x1, double x2)
{
  vector<double> temp(2);
  temp.push_back(x1);
  temp.push_back(x2);

  return Schaffer(temp);
}

void coordsSearch(vector<double> start, std::function<double(vector<double>)> f)
{
}

ostream& operator<<(ostream& os, const vector<double> vec)
{
  for (auto t : vec) {
    os << t << " ";
  }

  return os;
}

vector<double> operator+(const vector<double> v1, const vector<double> v2)
{
  auto ret = v1;
  for (unsigned int i = 0; i < ret.size(); ++i) {
    ret[i] += v2[i];
  }

  return ret;
}

vector<double> operator-(const vector<double> v1, const vector<double> v2)
{
  auto ret = v1;
  for (unsigned int i = 0; i < ret.size(); ++i) {
    ret[i] -= v2[i];
  }

  return ret;
}

vector<double> operator*(const vector<double> v1, const double d)
{
  auto ret = v1;
  for (auto& t : ret) {
    t *= d;
  }

  return ret;
}

struct Point {
  vector<double> x;
  double y;
};

ostream& operator<<(ostream& os, const Point& vec)
{
  os << vec.x << endl;
  os << vec.y;

  return os;
}

ostream& operator<<(ostream& os, const vector<Point> ps)
{
  for (auto t : ps) {
    os << t << endl;
  }
  os << endl;

  return os;
}

bool vector_diff(vector<double> x1, vector<double> x2)
{
  // return false;
  assert(x1.size() == x2.size());
  // assert(x1.size() == eps.size());
  bool ret = false;
  // cout << "x1: " << x1 << endl;
  // cout << "x2: " << x2 << endl;
  double sum = 0;
  for (unsigned int i = 0; i < x1.size(); ++i) {
    // cout << "diff smaller than eps: " << (abs(x1[i] - x2[i]) < 0.00001) << endl;
    sum += (abs(x1[i] - x2[i]));
  }

  return sum > 0.00001;
}

bool vector_diff(const vector<double>& x1, const vector<double>& x2, const vector<double>& eps)
{
  assert(x1.size() == x2.size());
  assert(x1.size() == eps.size());
  bool ret = true;
  for (unsigned int i = 0; i < x1.size(); ++i) {
    ret |= abs(x1[i] - x2[i]) < eps[i];
  }

  return ret;
}
