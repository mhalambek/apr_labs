#include "Matrix.hpp"
#include <iostream>

using namespace std;

int main()
{
  Matrix M1("mat1.txt");

  // cout << M1;
  const double d = 1.0 / 149.0;

  Matrix M2 = M1 * d;

  // cout << M2;

  // cout << (M1 / 2.0);
  M2 /= d;

  cout << "M1" << endl
       << M1 << endl;

  cout << "M2" << endl
       << M2 << endl;

  cout << "matrix eq " << (M1 == M2) << endl;

  return 0;
}
