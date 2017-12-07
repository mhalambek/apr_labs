#include "GoldenSectionSearch.hpp"
#include "Utils.hpp"

template <typename F>
Point GradientDescent(const Point& X0, bool useGSS, F& f, double eps, int maxIter = 10000)
{
  Point Xold;
  Point Xnew = X0;

  auto fGSS = [&](double lambda) {
    return f(Xold - lambda * f.df(Xold));
  };

  int iter = -1;
  do {
    Xold = Xnew;
    const double gamma = useGSS ? GoldenSectionSearch(1.0, eps, fGSS) : 1.0;
    Xnew = Xold - gamma * f.df(Xold);
    ++iter;
  } while (norm(Xnew - Xold) > eps && iter < maxIter);

  if (iter == maxIter)
    cout << "Solution not found in " << iter << " iterations" << endl;
  return Xnew;
}
