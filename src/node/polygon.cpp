#include "polygon.h"
#include <iostream>

void Polygon::add_triangle(const Vec3f A, const Vec3f B, const Vec3f C) {
    size_t size = data.size();
    data.resize(size + 3);
    data[size] = A;
    data[size + 1] = B;
    data[size + 2] = C;
}

std::vector<Vec3f> Polygon::get_data() {
    return this->data;
}

Polygon::Polygon(const std::string name) {
    this->set_name(name);
    data.resize(3);
    data[0] = {0, 0, 1};
    data[1] = {200, 0, 1};
    data[2] = {0, 10, 1};
    std::cout << "Polygon of name " << this->get_name() << " initialized as a basic triangle" << std::endl;
}

Polygon::~Polygon() {
    std::cout << "Polygon of name " << this->get_name() << " de-initialized" << std::endl;
}