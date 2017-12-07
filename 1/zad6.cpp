#include "Matrix.hpp"
#include <iostream>

using namespace std;

int main()
{
  Matrix mat("mat6.txt");
  Matrix y("y6.txt");

  cout << "mat" << endl
       << mat << endl;

  mat.LU();

  Matrix x = mat.LUforward(y);
  x = mat.LUbackward(x);

  mat.LUP();

  cout << "LUP x" << endl
       << x << endl;

  return 0;
}
