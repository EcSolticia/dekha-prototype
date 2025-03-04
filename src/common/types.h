#pragma once

#include <iostream>
#include <array>
#include <cmath>

typedef std::array<int, 2> Vec2;
typedef std::array<double, 2> Vec2f;
typedef std::array<double, 3> Vec3f;

inline void cout_Vec2f(const std::string prepend, Vec2f A, const std::string append) {
    std::cout << prepend << " (" << A[0] << ", " << A[1] << ") " << append << std::endl;
}

// returns -A
inline Vec2f invert(Vec2f A) {
    Vec2f C;
    C[0] = -A[0];
    C[1] = -A[1];
    return C;
}
// returns A + B
inline Vec2f add(Vec2f B, Vec2f A) {
    Vec2f C;
    C[0] = A[0] + B[0];
    C[1] = B[1] + C[1];
    return C;
}
// returns B - A
inline Vec2f subtract(Vec2f B, Vec2f A) {
    return add(B, invert(A));
}
// returns A * b
inline Vec2f multiply(Vec2f A, double b) {
    Vec2f C;
    C[0] = A[0] * b;
    C[1] = A[1] * b;
    return C;
}
// returns B/A
inline Vec2f divide(Vec2f B, Vec2f A) {
    Vec2f C;
    C[0] = B[0]/A[0];
    C[1] = B[1]/A[1];
    return C;
}
inline Vec2f divide(Vec2f B, double a) {
    Vec2f C;
    C[0] = B[0]/a;
    C[1] = B[1]/a;
    return C;
}
inline double length(Vec2f A) {
    return sqrt(pow(A[0], 2) + pow(A[1], 2));
}