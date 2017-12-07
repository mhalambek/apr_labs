#pragma once
#include "EvaluatedSolution.hpp"
#include <random>
#include <vector>

using namespace std;

template <typename S>
void calculateFitness(vector<EvaluatedSolution<S> >& vec)
{
  double fitnessSum = 0;
  double minFitness = numeric_limits<double>::max();

  for (auto& s : vec) {
    s.fitness = 1 / s.fuctionValue;
    fitnessSum += s.fitness;
    if (s.fitness < minFitness) {
      minFitness = s.fitness;
    }
  }

  fitnessSum -= vec.size() * minFitness;

  for (auto& s : vec) {
    s.fitness -= minFitness;
    s.fitness /= fitnessSum;
  }
};

template <typename E>
E& proportionalSelection(vector<E>& vec)
{
  random_device dev;
  uniform_real_distribution<double> selectDis(0, 1);

  double chance = selectDis(dev);
  auto& ret = vec.front();

  for (auto& a : vec) {
    chance -= a.fitness;
    if (chance < 0) {
      ret = a;
      break;
    }
  }

  return ret;
}

template <typename S>
S getChild(vector<EvaluatedSolution<S> >& pop)
{
  auto& mom = proportionalSelection(pop).sol;
  auto& dad = proportionalSelection(pop).sol;

  return dad * mom;
}

template <typename T>
void mutate(SolutionDecimal<T>& sol)
{
  random_device dev;
  uniform_real_distribution<T> dis(-0.01, 0.01);
  normal_distribution<T> n;
  for (unsigned int i = 0; i < sol.size(); ++i) {
    if (dis(dev) > 0) {
      sol[i] += n(dev);
    } else {
      sol[i] += dis(dev);
    }
  }
  sol.repair();
}

template <typename T>
void mutate(SolutionBit<T>& sol)
{
  random_device dev;
  uniform_real_distribution<T> dis(0, 1);
  for (auto& a : sol.data) {
    for (auto b : a) {
      if (dis(dev) > 0.95) {
        b = ~b;
      }
    }
  }
}
