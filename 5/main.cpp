#include "Matrix.hpp"
#include "RungeKuttaMethod.hpp"
#include "TrapezoidalApproximation.hpp"
#include "Utils.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

int main()
{
  cout.precision(3);

  const Point B_m(2, 0.0);
  const Matrix A_m("A_m.txt");
  const Point X0_m = { 0.0, 2.0 };
  cout << "Zadatak 1:" << endl;
  cout << "  Runge-Kutta:" << endl
       << endl;
  const NumIntInfos rk1 = RungeKuttaMethod(X0_m, A_m, B_m, 0.1, 10.0);
  cout << "  Trepezoid:" << endl
       << endl;
  const NumIntInfos ta1 = TrapezoidalApproximation(X0_m, A_m, B_m, 0.1, 10.0);

  const Point B_f(2, 0.0);
  const Matrix A_f("A_f.txt");
  const Point X0_f = { 1.0, -2.0 };
  cout << "Zadatak 2:" << endl;
  cout << "  Runge-Kutta:" << endl
       << endl;
  const NumIntInfos rk2 = RungeKuttaMethod(X0_f, A_f, B_f, 0.02, 10);
  cout << "  Trepezoid:" << endl;
  const NumIntInfos ta2 = TrapezoidalApproximation(X0_f, A_f, B_f, 0.1, 10);

  rk1[0].ToFile("rk1_pos.txt");
  rk1[1].ToFile("rk1_vel.txt");
  rk2[0].ToFile("rk2_pos.txt");
  rk2[1].ToFile("rk2_vel.txt");

  ta1[0].ToFile("ta1_pos.txt");
  ta1[1].ToFile("ta1_vel.txt");
  ta2[0].ToFile("ta2_pos.txt");
  ta2[1].ToFile("ta2_vel.txt");

  return 0;
}
