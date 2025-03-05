#include "camera.h"

void Camera::set_dimensions(Vec2f dimensions) {
    cout_vecf<2, true>("Set camera dimensions to", dimensions, "");
    this->dimensions = dimensions;
}
Vec2f Camera::get_dimensions() {
    return this->dimensions;
}

void Camera::set_focal_length(const double focal_length) {
    this->focal_length = focal_length;
}

double Camera::get_focal_length() const {
    return this->focal_length;
}

void Camera::add_to_channel(Node* node) {
    std::cout << "Added node " << node << " to channel of camera named " << this->get_name() << std::endl;
    channel.push_back(node);
}

void Camera::set_channel(const std::vector<Node*> channel) {
    this->channel = channel;
    std::cout << "Camera (" << this->get_name() << ") channel changed" << std::endl;
}
std::vector<Node*> Camera::get_channel() const {
    return this->channel;
}

Camera::Camera(const std::string name) {
    this->set_name(name);
    this->focal_length = 10;
    std::cout << "Camera node of name " << this->get_name() << " constructed with focal_length = " << 10 << std::endl;
}

Camera::~Camera() {
    std::cout << "Camera node of name " << this->get_name() << " with focal_length = " << focal_length << " desctructed" << std::endl;
}