#pragma once
#include <cassert>
#include <iostream>
#include <ostream>
#include <random>
#include <vector>

using namespace std;

typedef vector<bool> bits;

ostream& operator<<(ostream& os, const bits& b)
{
  for (auto p : b) {
    os << p << " ";
  }

  return os;
}

template <typename T>
struct SolutionBit {
  vector<bits> data;
  vector<T> max, min;
  static unsigned int dim;
  static unsigned int prec;

  SolutionBit(vector<T> _max, vector<T> _min)
      : max{ _max }
      , min{ _min }
  {
    assert(max.size() == dim);
    assert(min.size() == dim);
    for (unsigned int i = 0; i < dim; ++i) {
      data.push_back(bits(prec));
    }
  };

  SolutionBit(T _max, T _min)
      : SolutionBit(vector<T>(dim, _max), vector<T>(dim, _min))
  {
    data = vector<bits>(dim);
    for (unsigned int i = 0; i < dim; ++i) {
      data[i] = bits(prec);
    }
  };

  SolutionBit(const vector<unsigned int>& precision, vector<T>& _max, vector<T>& _min)
      : max{ _max }
      , min{ _min }
  {

    for (auto& p : precision) {
      data.push_back(bits(p));
    }
  };

  SolutionBit(const SolutionBit& a)
  {
    data = a.data;
    max = a.max;
    min = a.min;
  };

  T operator[](unsigned int elemIndex)
  {
    T ret = 0;
    unsigned long maxVal = 1, minVal = 0;
    unsigned long l = data[elemIndex].front();

    for (unsigned int i = 1; i < data[elemIndex].size(); ++i) {
      l <<= 1;
      l += data[elemIndex][i];
      maxVal <<= 1;
      maxVal += 1;
    }

    return (T)l / (maxVal - minVal) * (max[elemIndex] - min[elemIndex]) + min[elemIndex];
  };

  operator vector<T>()
  {
    vector<T> ret(size());

    for (unsigned int i = 0; i < ret.size(); ++i) {
      ret[i] = (*this)[i];
    }

    return ret;
  }

  unsigned int size() const
  {

    return data.size();
  }

  friend ostream& operator<<(ostream& os, const SolutionBit& b)
  {
    for (auto k : b.data) {
      os << k << endl;
    }

    return os;
  };

  bool operator==(const SolutionBit& cmp)
  {

    return data == cmp.data;
  };

  SolutionBit operator*(SolutionBit& a)
  {
    auto ret = *this;
    random_device dev;
    int numOfBits = 0;
    uniform_real_distribution<float> dis(0, 1);
    if (dis(dev) > 0.5) {
      for (unsigned int i = 0; i < data.size(); ++i) {
        if (dis(dev) > 0.5) {
          ret.data.push_back(data[i]);
        } else {
          ret.data.push_back(a.data[i]);
        }
      }

      return ret;
    }
    for (auto& p : data) {
      numOfBits += p.size();
    }
    unsigned int breakPos = uniform_int_distribution<unsigned int>(0, numOfBits - 1)(dev);
    // breakPos = 4;
    // cout << "breakPos: " << breakPos << endl;
    int breakRowIndex = 0;
    while (breakPos > data[breakRowIndex].size()) {
      breakPos -= data[breakRowIndex++].size();
    }
    // cout << "breakRowIndex: " << breakRowIndex << endl;
    // cout << "breakPos: " << breakPos << endl;

    for (unsigned int i = breakPos; i < ret.data[breakRowIndex].size(); ++i) {
      ret.data[breakRowIndex][i] = a.data[breakRowIndex][i];
    }

    for (unsigned int i = breakRowIndex + 1; i < data.size(); ++i) {
      ret.data[i] = a.data[i];
    }

    repair();
    return ret;
  };
  void repair()
  {
    if (data.size() > dim) {
      data.erase(data.begin() + dim, data.end());
    }
  }
};

template <typename T>
unsigned int SolutionBit<T>::dim = 0;

template <typename T>
unsigned int SolutionBit<T>::prec = 10;
