#pragma once

#include "node.h"
#include <vector>

class Camera : public Node {
    float FOV;
    std::vector<Node*> channel;
    void* screen_ptr;

public:
    void set_FOV(const float FOV);
    float get_FOV() const;

    void set_channel(const std::vector<Node*> channel);
    std::vector<Node*> get_channel() const;

    void set_screen(void* screen_ptr);
    void* get_screen() const;

    Camera(const std::string name="Non-name");
    ~Camera() override;
};