#pragma once 
#include <cmath>
#include "types.h"

double max(double a, double b, double c) {
    return std::max(a, std::max(b, c));
}
double min(double a, double b, double c) {
    return std::min(a, std::min(b, c));
}

double dot_prod(Vec3f A, Vec3f B) {
    return A[0] * B[0] + A[1] * B[1] + A[2] * B[2];
}
double dot_prod(Vec2f A, Vec2f B) {
    return A[0] * B[0] + A[1] * B[1];
}