#include "FunctionCounter.hpp"
#include "GA.hpp"
#include "SolutionBit.hpp"
#include "SolutionDecimal.hpp"
#include "functions.hpp"
#include <math.h>
#include <random>
#include <string>

using namespace std;

unsigned int numOfBits(const unsigned int numberOfDecimals, const double max, const double min)
{

  return log(1 + (max - min) * pow(10, numberOfDecimals)) / log(2.0);
}

//popSize
//bit or decimal
//
//decimal
//function
int main(int argc, char** argv)
{
  unsigned int populationSize = 100;
  unsigned int functionEval = 10000;
  bool useBit = false;

  assert(argc > 4);
  populationSize = stoi(argv[1]);
  functionEval = stoi(argv[2]);
  useBit = stoi(argv[3]);
  unsigned int problemDimension = 2;
  if (argc > 5) {
    problemDimension = stoi(argv[5]);
  }
  unsigned int functionNumber = stoi(argv[4]);
  std::unique_ptr<FunctionCounter> fc;

  switch (functionNumber) {
  case 1:
    problemDimension = 2;
    fc = std::unique_ptr<FunctionCounter>(new FunctionCounter(f1));
    break;
  case 2:
    problemDimension = 2;
    fc = std::unique_ptr<FunctionCounter>(new FunctionCounter(f2));
    break;
  case 3:
    fc = std::unique_ptr<FunctionCounter>(new FunctionCounter(f3));
    break;
  case 4:
    fc = std::unique_ptr<FunctionCounter>(new FunctionCounter(f4));
    break;
  case 6:
    fc = std::unique_ptr<FunctionCounter>(new FunctionCounter(f6));
    break;
  case 7:
    fc = std::unique_ptr<FunctionCounter>(new FunctionCounter(f7));
    break;
  default:
    assert(false);
  }

  if (useBit) {
    GA<SolutionBit<double> > algo(*fc, functionEval, populationSize, problemDimension);
    SolutionBit<double>::prec = numOfBits(4, algo.max, algo.min);
    algo.run();
    cout << (vector<double>)algo.best.sol << endl;
  } else {
    GA<SolutionDecimal<double> > ga(*fc, functionEval, populationSize, problemDimension);
    ga.run();
    cout << ga.best.sol << endl;
  }

  //initialize pop
  //calculate fitness
  //while --maxIter
  //make nextgen
  //if elite put best

  return 0;
}
