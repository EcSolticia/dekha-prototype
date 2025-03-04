#include "camera.h"

void Camera::set_FOV(const float FOV) {
    this->FOV = FOV;
}

float Camera::get_FOV() const {
    return this->FOV;
}

void Camera::set_channel(const std::vector<Node*> channel) {
    this->channel = channel;
    std::cout << "Camera (" << this->get_name() << ") channel changed" << std::endl;
}
std::vector<Node*> Camera::get_channel() const {
    return this->channel;
}

void Camera::set_screen(void* screen_ptr) {
    this->screen_ptr = screen_ptr;
    std::cout << "Camera (" << this->get_name() <<") screen_ptr member set to " << &screen_ptr << std::endl;
}
void* Camera::get_screen() const {
    return this->screen_ptr;
}

Camera::Camera(const std::string name) {
    this->set_name(name);
    this->FOV = 10;
    std::cout << "Camera node of name " << this->get_name() << " constructed with FOV = " << 10 << std::endl;
}

Camera::~Camera() {
    std::cout << "Camera node of name " << this->get_name() << " with FOV = " << FOV << " desctructed" << std::endl;
}