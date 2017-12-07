#pragma once
#include "EvaluatedSolution.hpp"
#include "FunctionCounter.hpp"
#include "randomize.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>

template <typename S>
class GA {
  public:
  EvaluatedSolution<S> best;
  unsigned int currentEvalCount = 0, maxFunctionEval;
  FunctionCounter fn;
  unsigned int populationSize;
  unsigned int problemDimension;
  double min = -50, max = 150;
  bool elite = true;
  vector<EvaluatedSolution<S> > population;
  GA(FunctionCounter _fn, unsigned int _maxFunctionEval, unsigned int _populationSize, unsigned int _problemDimension)
      : fn{ _fn }
      , maxFunctionEval{ _maxFunctionEval }
      , populationSize{ _populationSize }
      , problemDimension{ _problemDimension }
      , best{ EvaluatedSolution<S>(S(-100, 100), _fn) }
  {
    S::dim = problemDimension;
  };
  void run()
  {
    initializePopulation();
    //evaluate whole pop
    best = population.front();
    while (fn.callsNum < maxFunctionEval) {
      //calc fitness
      cout << "number of fun calls: " << fn.callsNum << endl;
      cout << best.fuctionValue << endl;
      cout << (vector<double>)best.sol << endl;
      calculateFitness(population);
      for (auto p : population) {
        if (p.fuctionValue < best.fuctionValue) {
          best = p;
        }
      }
      vector<EvaluatedSolution<S> > nextGen;
      if (elite) {
        nextGen.push_back(best);
      }
      while (nextGen.size() < populationSize) {
        auto child = getChild(population);
        mutate(child);
        child.repair();
        nextGen.push_back(EvaluatedSolution<S>(child, fn));
      }
      population = nextGen;
    }
  };

  private:
  void initializePopulation()
  {
    unsigned int a = populationSize;
    while (a--) {
      S sol(max, min);
      randomize(sol);
      sol.repair();
      population.push_back(EvaluatedSolution<S>(sol, fn));
    }
  };
};
