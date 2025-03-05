#pragma once

#include "node.h"
#include "polygon.h"
#include <vector>

class Camera : public Node {
    double focal_length;
    std::vector<Node*> channel;

    Vec2f dimensions;

private:
    Vec2f get_position_on_screen(Vec3f vertex_position);

public:

    void set_dimensions(Vec2f dimensions);
    Vec2f get_dimensions();

    void set_focal_length(const double focal_length);
    double get_focal_length() const;

    void add_to_channel(Node* node);
    void set_channel(const std::vector<Node*> channel);
    std::vector<Node*> get_channel() const;

    Camera(const std::string name="Non-name");
    ~Camera() override;
};