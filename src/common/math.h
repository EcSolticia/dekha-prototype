#pragma once 
#include <cmath>
#include "types.h"

double max(double a, double b, double c) {
    return std::max(a, std::max(b, c));
}
double min(double a, double b, double c) {
    return std::min(a, std::min(b, c));
}