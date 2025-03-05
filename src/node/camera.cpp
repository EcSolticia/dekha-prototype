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

void Camera::add_to_channel(Node* node) {
    channel.push_back(node);
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

// DO NOT CALL function yet
// Still not done
void Camera::render_polygon(Polygon* node) {
    if (this->get_screen() == nullptr) {
        std::cout << "Cannot render polygon as no screen is provided" << std::endl;
        // throw error than simply return as there is no sense in continuing the program
        // if the screen is not provided
        throw -2;
    }

    std::vector<Vec3f> data = node->get_data();

    if (data.size() != 3) {
        std::cout << "Non-triangle rendering is not supported" << std::endl;
        throw -2;
    }

    Vec3f zero = {0, 0, 0};
    if (this->get_rotation() != zero) {
        std::cout << "Non-zero rotations are not yet implemented" << std::endl;
        throw -2;
    }

    Vec3f origin = this->get_position();
    Vec3f A = data[0];
    Vec3f B = data[1];
    Vec3f C = data[2];

    //Vec3f rel_A = subtract(A, origin);

}

Camera::Camera(const std::string name) {
    this->set_name(name);
    this->focal_length = 10;
    std::cout << "Camera node of name " << this->get_name() << " constructed with focal_length = " << 10 << std::endl;
}

Camera::~Camera() {
    std::cout << "Camera node of name " << this->get_name() << " with focal_length = " << focal_length << " desctructed" << std::endl;
}