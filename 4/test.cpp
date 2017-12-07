#include "FunctionCounter.hpp"
#include "GA.hpp"
#include "SolutionBit.hpp"
#include "SolutionDecimal.hpp"
#include "functions.hpp"
#include "randomize.hpp"
#include "utils.hpp"
#include <cassert>
#include <iostream>
#include <ostream>

using namespace std;

typedef SolutionBit<double> DoubleBit;

int main()
{
  vector<double> min(2, -2);
  // cout << "min: " << min << endl;
  vector<double> max(2, 2);
  // cout << "max: " << max << endl;
  vector<unsigned int> v(2, 3);
  DoubleBit::dim = 3;
  DoubleBit sol(v, max, min);

  sol.data[0] = bits(sol.data[0].size(), 0);
  sol.data[1] = bits(sol.data[1].size(), 1);

  sol = DoubleBit(2, -2);

  assert(sol[0] == -2);
  sol.data[1] = bits(3, 1);
  assert(sol[1] == 2);

  SolutionDecimal<double> dec(2, 2, 2);

  dec[0] = 1;
  dec[1] = 1;

  FunctionCounter fc(f1);
  assert(fc(dec) == 0);

  sol = DoubleBit(2, 0);
  fc = FunctionCounter(f6);

  assert(fc(sol) == 0);
  assert(fc.callsNum == 1);

  DoubleBit sol2 = sol;
  randomize(sol);
  // cout << "sol:" << endl
  //      << sol << endl;
  // cout << "sol2:" << endl
  //      << sol2 << endl;

  assert(!(sol == sol2));
  dec = SolutionDecimal<double>(2, 2, -2);

  auto dec2 = dec;

  randomize(dec);
  assert(!(dec == dec2));

  SolutionDecimal<double>::dim = 2;

  assert(SolutionDecimal<double>(2, -2).data == vector<double>(2, 0));

  vector<EvaluatedSolution<SolutionDecimal<double> > > vecPop;
  EvaluatedSolution<SolutionDecimal<double> > eSol(dec, fc);
  eSol.fuctionValue = 1;
  vecPop.push_back(eSol);
  eSol.fuctionValue = 2;
  vecPop.push_back(eSol);
  eSol.fuctionValue = 3;
  vecPop.push_back(eSol);
  eSol.fuctionValue = 4;
  vecPop.push_back(eSol);

  calculateFitness(vecPop);

  double sum = 0;
  for (auto s : vecPop) {
    sum += s.fitness;
  }

  assert((sum < 1.00001) && (sum > 0.99999));

  GA<SolutionDecimal<double> > ga(FunctionCounter(f6), 12, 10, 2);
  ga.run();

  sol2 = sol;
  // cout << sol << endl;
  mutate(sol);
  // cout << sol << endl;
  // assert(!(sol == sol2));

  sol.data[0] = bits(3, 0);
  sol.data[1] = bits(3, 0);

  sol2.data[0] = bits(3, 1);
  sol2.data[1] = bits(3, 1);
  auto child = (sol * sol2);
  GA<SolutionBit<double> > galgo(FunctionCounter(f6), 12, 10, 2);
  galgo.run();

  return 0;
}
