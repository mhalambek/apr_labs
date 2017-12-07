#include "Matrix.hpp"
#include <iostream>

using namespace std;

int main()
{
  Matrix mat("mat2.txt");
  Matrix y("y2.txt");

  // cout << "mat" << endl
  //      << mat << endl;
  Matrix lu(mat.data);
  lu.LU();
  Matrix luP = mat.LUP();

  cout << "mat after LUP" << endl
       << mat << endl;
  // cout << "mat LUP" << endl
  //      << luP << endl;
  // cout << "y: " << endl
  //      << y << endl;

  y = luP * y;

  // cout << lu << endl;

  cout << "y:" << endl
       << y << endl;

  Matrix x = mat.LUforward(y);
  cout << "after LU LUforward: " << endl
       << x << endl;
  x = mat.LUbackward(x);

  cout << "LUP x " << endl
       << x << endl;

  return 0;
}
