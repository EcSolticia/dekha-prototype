#include "polygon.h"
#include <iostream>

void Polygon::add_triangle(const Vec3f A, const Vec3f B, const Vec3f C) {
    size_t size = data.size();
    data.resize(size + 3);
    data[size] = A;
    data[size + 1] = B;
    data[size + 2] = C;
}

Polygon::Polygon() {
    data.resize(3);
    data[0] = {0, 0, 0};
    data[1] = {1, 0, 0};
    data[2] = {0, 1, 0};
    std::cout << "Polygon initialized as a basic triangle" << std::endl;
}

Polygon::~Polygon() {
    std::cout << "Polygon de-initialized" << std::endl;
}