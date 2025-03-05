#pragma once

#include "node.h"
#include "polygon.h"
#include <vector>

class Camera : public Node {
    double focal_length;
    double fov;
    std::vector<Node*> channel;
    void* screen_ptr = nullptr;

public:
    void set_fov(const double fov);
    double get_fov() const;

    void set_focal_length(const double focal_length);
    double get_focal_length() const;

    void add_to_channel(Node* node);
    void set_channel(const std::vector<Node*> channel);
    std::vector<Node*> get_channel() const;

    void set_screen(void* screen_ptr);
    void* get_screen() const;

    void render_polygon(Polygon* node);

    Camera(const std::string name="Non-name");
    ~Camera() override;
};