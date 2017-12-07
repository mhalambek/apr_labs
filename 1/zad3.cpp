#include "Matrix.hpp"
#include <iostream>

using namespace std;

int main()
{
  Matrix mat("mat3.txt");
  Matrix y("y3.txt");
  Matrix mat2 = mat;

  cout << "mat LU" << endl
       << mat << endl;

  mat2.LUP();

  cout << "mat LUP" << endl
       << mat2 << endl;

  return 0;
}
