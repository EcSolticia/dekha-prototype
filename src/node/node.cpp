#include "node.h"

void Node::set_name(const std::string name) {
    this->name = name;
}
std::string Node::get_name() const {
    return this->name;
}

void Node::set_position(const Vec3f position) {
    this->position = position;
}
Vec3f Node::get_position() const {
    return this->position;
}

void Node::set_rotation(const Vec3f rotation) {
    this->rotation = rotation;
}
Vec3f Node::get_rotation() const {
    return rotation;
}

Node::Node(const std::string name) {
    this->set_name(name);
    Vec3f zero = {};
    this->position = zero;
    this->rotation = zero;
    std::cout << "Node of name " << this->get_name() << " constructed" << std::endl;
}

Node::~Node() {
    std::cout << "Node of name " << this->get_name() << " desctructed" << std::endl;
}