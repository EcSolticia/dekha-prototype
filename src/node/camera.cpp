#include "camera.h"

void Camera::set_fov(const double fov) {
    this->fov = fov;
}
double Camera::get_fov() const {
    return this->fov;
}

void Camera::set_focal_length(const double focal_length) {
    this->focal_length = focal_length;
}

double Camera::get_focal_length() const {
    return this->focal_length;
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
    this->focal_length = 10;
    std::cout << "Camera node of name " << this->get_name() << " constructed with focal_length = " << 10 << std::endl;
}

Camera::~Camera() {
    std::cout << "Camera node of name " << this->get_name() << " with focal_length = " << focal_length << " desctructed" << std::endl;
}