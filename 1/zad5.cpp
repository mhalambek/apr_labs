#include "Matrix.hpp"
#include <iostream>

using namespace std;

int main()
{
  Matrix mat("mat5.txt");
  Matrix y("y5.txt");
  Matrix mat2 = mat;

  mat2.LU();
  Matrix xLU = mat2.LUforward(y);
  xLU = mat2.LUbackward(y);

  cout << "x LU :" << endl
       << xLU << endl;

  Matrix P = mat.LUP();

  y = P * y;
  Matrix x = mat.LUforward(y);
  x = mat.LUbackward(x);

  cout << "LUP x" << endl
       << x << endl;

  return 0;
}
