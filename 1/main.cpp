#include "Matrix.hpp"
#include <iostream>

void lora(std::string head, Matrix mat, Matrix y)
{
  Matrix b = mat.LU().LUforward(y);
  cout << "LU" << endl;
  cout << mat.LU() << endl;
  cout << head << "LU" << endl
       << mat.LU().LUbackward(b) << endl;
  Matrix bLUP = mat.LUP().LUforward(y);
  cout << head << "LUP" << endl
       << mat.LUP().LUbackward(bLUP) << endl;
}

int main()
{
  Matrix M1("A.txt");

  // cout << M1;
  const double d = 1 / 3;

  Matrix M2 = M1 * d;

  // cout << M2;

  // cout << (M1 / 2.0);
  M2 /= d;

  // cout << (M1 == M2) << endl;
  Matrix mat("squareA.txt");
  // cout << "A LU" << endl
  //      << mat.LU() << endl;
  //
  // cout << "A LUP" << endl
  //      << mat.LUP() << endl;

  // // Matrix y("y.txt");
  // // //
  // Matrix b = mat.LU().LUforward(y);
  // cout << "b " << endl
  //      << b << endl;
  // //
  // Matrix x = mat.LU().LUbackward(y);
  // cout << "x " << endl
  //      << x << endl;
  // cout << mat.LU().LUbackward(y) << endl;
  Matrix LUPmat("LUPmat.txt");

  vector<double> temp({ 1, 2, 3 });
  vector<vector<double> > temp2;
  temp2.push_back(temp);
  // cout
  //     << LUPmat.LUP().LUbackward(Matrix(temp2));
  // cout << LUPmat.LU().LUbackward(Matrix(temp2));
  // lora("1 2 3 .. ", LUPmat, Matrix(temp2));
  // Matrix decimalMat("decimalMat.txt");
  // Matrix decimalY("decimalY.txt");
  //
  // Matrix decimalB = decimalMat.LU().LUforward(decimalY);
  // cout << "decimal sol LU" << endl
  //      << decimalMat.LU().LUbackward(decimalB) << endl;
  // sigsegv dump
  // cout << "decimal sol LUP" << endl
  //      << decimalMat.LUP().LUbackward(decimalY) << endl;
  //

  Matrix sus("sus.txt");
  Matrix susY("susY.txt");
  lora("sus ", sus, susY);
  // b = sus.LU().LUforward(susY);
  // cout << "sus LU" << endl
  //      << sus.LU().LUbackward(b)
  //      << endl;
  //core dump
  // cout << "sus LUP" << endl
  //      << sus.LUP().LUforward(susY)
  //      << endl;

  // Matrix finalMat("finalMat.txt");
  // Matrix finalY("finalY.txt");
  //
  // lora("final ", finalMat, finalY);

  return 0;
}
