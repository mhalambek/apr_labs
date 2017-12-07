#pragma once
#include <ostream>
#include <random>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vec)
{
  for (auto& a : vec) {
    os << a << " ";
  }

  return os;
}

template <typename T>
class SolutionDecimal {
  public:
  vector<T> data, min, max;
  static unsigned int dim;

  SolutionDecimal(unsigned int dim, vector<T> _max, vector<T> _min)
      : data{ vector<T>(dim) }
      , max{ _max }
      , min{ _min } {};

  SolutionDecimal(unsigned int dim, T _max, T _min)
      : SolutionDecimal(dim, vector<T>(dim, _max), vector<T>(dim, _min)){};

  SolutionDecimal(T max, T min)
      : SolutionDecimal(dim, max, min){};

  SolutionDecimal(vector<T> max, vector<T> min)
      : SolutionDecimal(dim, max, min){};

  SolutionDecimal(const SolutionDecimal& a)
      : data{ a.data }
      , max{ a.max }
      , min{ a.min } {};

  auto begin() { data.begin(); };
  auto end() { data.end(); };

  auto& operator[](const unsigned int i)
  {
    return data[i];
  };

  operator vector<T>()
  {
    return data;
  }

  unsigned int size() const
  {
    return data.size();
  };
  bool operator==(const SolutionDecimal& a)
  {
    return a.data == data;
  }

  friend ostream& operator<<(ostream& os, const SolutionDecimal& a)
  {
    os << a.data;

    return os;
  };
  SolutionDecimal operator*(SolutionDecimal& p2)
  {
    auto ret = *this;
    random_device dev;
    uniform_real_distribution<float> op(0, 1);
    if (op(dev) > 0.5) {
      for (int i = 0; i < ret.size(); ++i) {
        ret[i] = (data[i] + p2[i]) / 2;
      }
    } else {
      for (int i = 0; i < ret.size(); ++i) {
        if (op(dev) > 0.5) {
          ret[i] = data[i];
        } else {
          ret[i] = p2[i];
        }
      }
    }

    return ret;
  }
  void repair()
  {
    random_device dev;
    for (unsigned int i = 0; i < data.size(); ++i) {
      if (data[i] > max[i] || data[i] < min[i]) {
        data[i] = uniform_real_distribution<T>(min[i], max[i])(dev);
      }
    }
  }
};

template <typename T>
unsigned int SolutionDecimal<T>::dim = 0;
