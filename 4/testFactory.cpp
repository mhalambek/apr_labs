#include "SolutionBit.hpp"
#include "SolutionDecimal.hpp"
#include "SolutionFactory.hpp"
#include <iostream>

int main(int argc, char** argv)
{
  SolutionFactory<SolutionDecimal<double>, double> solDecFac(150, -50);
  SolutionDecimal<double>::dim = 2;
  assert((vector<double>)solDecFac() == vector<double>(2, 0));

  SolutionBit<double>::dim = 2;
  SolutionFactory<SolutionBit<double>, double> solDecBit(150, -50);
  assert((vector<double>)solDecBit() == vector<double>(2, -50));

  return 0;
}
