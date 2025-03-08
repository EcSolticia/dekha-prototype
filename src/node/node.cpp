#include "node.h"

void Node::set_name(const std::string name) {
    this->name = name;
}
std::string Node::get_name() const {
    return this->name;
}

void Node::set_position(const Vector3 position) {
    this->position = position;
}
Vector3 Node::get_position() const {
    return this->position;
}

void Node::set_rotation(const Vector3 rotation) {
    this->rotation = rotation;
}
Vector3 Node::get_rotation() const {
    return rotation;
}

Node::Node(const std::string name) {
    this->set_name(name);
    this->position = Vector3();
    this->rotation = Vector3();
    std::cout << "Node of name " << this->get_name() << " constructed" << std::endl;
}

Node::~Node() {
    std::cout << "Node of name " << this->get_name() << " desctructed" << std::endl;
}