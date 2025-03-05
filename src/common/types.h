#pragma once

#include <iostream>
#include <array>
#include <cmath>

typedef std::array<int, 2> Vec2;
typedef std::array<double, 2> Vec2f;
typedef std::array<double, 3> Vec3f;

template<size_t N> void cout_vecf(const std::string prepend, std::array<double, N> A, const std::string append) {
    std::cout << prepend << " (";
    for (size_t i = 0; i < N - 1; ++i) {
        std::cout << A[i] << ", ";
    }
    std::cout << A[N - 1] << ")" << append << std::endl;
}

template<size_t N> std::array<double, N> invert(std::array<double, N> A) {
    std::array<double, N> C;
    for (size_t i = 0; i < N; ++i) {
        C[i] = -A[i];
    }
    return C;
}
template<size_t N> std::array<double, N> add(std::array<double, N> A, std::array<double, N> B) {
    std::array<double, N> C;
    for (size_t i = 0; i < N; ++i) {
        C[i] = A[i] + B[i];
    }
    return C;
}
template<size_t N> std::array<double, N> subtract(std::array<double, N> B, std::array<double, N> A) {
    return add<N>(B, invert<N>(A));
}
template<size_t N> std::array<double, N> multiply(std::array<double, N> B, double a) {
    std::array<double, N> C;
    for (size_t i = 0; i < N; ++i) {
        C[i] = B[i] * a;
    }    
    return C;
}
template<size_t N> std::array<double, N> divide(std::array<double, N> B, double a) {
    if (a == 0) {
        std::cout << "Math error: Division by zero!" << std::endl;
        throw -100;
    }
    std::array<double, N> C;
    for (size_t i = 0; i < N; ++i) {
        C[i] = B[i]/a;
    }
    return C;
}
template<size_t N> double length(std::array<double, N> A) {
    double result_sq = 0;
    for (size_t i = 0; i < N; ++i) {
        result_sq += pow(A[i], 2);
    }
    return sqrt(result_sq);
}
/*
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
}*/