#pragma once

#include <iostream>

#include <exception>

#include <array>
#include <cmath>

typedef std::array<int, 2> Vec2;
typedef std::array<double, 2> Vec2f;
typedef std::array<double, 3> Vec3f;

template<size_t N, bool flush> void cout_vecf(const std::string prepend, std::array<double, N> A, const std::string append) {
    std::cout << prepend << " (";
    for (size_t i = 0; i < N - 1; ++i) {
        std::cout << A[i] << ", ";
    }
    std::cout << A[N - 1] << ")" << append;
    if (flush) {
        std::cout << std::endl;
    }
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
        std::string msg = "Division by zero!";
        throw std::domain_error(msg);
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
