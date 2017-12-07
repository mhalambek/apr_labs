#include "FunctionCounter.hpp"
#include "GA.hpp"
#include "SolutionBit.hpp"
#include "SolutionDecimal.hpp"
#include "functions.hpp"
#include <random>
#include <string>

using namespace std;

unsigned int populationSize = 100;
unsigned int functionEval = 10000;

template <typename S>
void runGa()
{
  GA<S, double> algo(FunctionCounter(f1), functionEval,
      populationSize, SolutionFactory<S, double>(150, -50));
  // algo.run();
  // cout << "f1: " << (vector<double>)algo.best.sol << endl;
}

int main(int argc, char** argv)
{
  bool useBit = false;

  assert(argc > 3);
  populationSize = stoi(argv[1]);
  functionEval = stoi(argv[2]);
  useBit = stoi(argv[3]);

  if (useBit) {
    runGa<SolutionBit<double> >();
  } else {
    runGa<SolutionDecimal<double> >();
  }

  return 0;
}
