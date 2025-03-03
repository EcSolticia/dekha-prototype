#include "node.h"

void Node::set_position(const Vec3f position_p) {
    position = position_p;
}
Vec3f Node::get_position() const {
    return position;
}

void Node::set_rotation(const Vec3f rotation_p) {
    rotation = rotation_p;
}
Vec3f Node::get_rotation() const {
    return rotation;
}

Node::Node() {
    Vec3f zero = {};
    position = zero;
    rotation = zero;
    std::cout << "Node constructed" << std::endl;
}

Node::~Node() {
    std::cout << "Node desctructed" << std::endl;
}