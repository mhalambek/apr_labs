#pragma once
#include <vector>

using Point = std::vector<double>;

Point HookeJeeves(const Point& X0, double Dx, double (*f)(const Point&), double eps);
