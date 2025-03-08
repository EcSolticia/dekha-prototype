#include "polygon.h"
#include <iostream>

void Polygon::set_data(const std::vector<Vector3> data) {
    this->data = data;
}
std::vector<Vector3> Polygon::get_data() const {
    return this->data;
}

Polygon::Polygon(const std::string name) {
    this->set_name(name);
    data.resize(3);
    data[0] = Vector3(0, 0, 1);
    data[1] = Vector3(10, 0, 1);
    data[2] = Vector3(0, 20, 2);
    std::cout << "Polygon of name " << this->get_name() << " initialized as a basic triangle" << std::endl;
}

Polygon::~Polygon() {
    std::cout << "Polygon of name " << this->get_name() << " de-initialized" << std::endl;
}