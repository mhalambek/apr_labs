#include "Matrix.hpp"
#include <iostream>

using namespace std;

int main()
{
  Matrix mat("mat4.txt");
  Matrix y("y4.txt");
  Matrix mat2 = mat;

  mat.LU();
  Matrix x1 = mat.LUforward(y);
  x1 = mat.LUbackward(x1);

  cout << "LU x" << endl
       << x1 << endl;

  Matrix P = mat2.LUP();
  y = P * y;
  x1 = mat2.LUforward(y);
  x1 = mat2.LUbackward(x1);

  cout << "LUP x" << endl
       << x1 << endl;

  return 0;
}
