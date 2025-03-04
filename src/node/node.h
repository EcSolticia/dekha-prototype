#pragma once
#include <iostream>
#include <string>
#include "../common/types.h"

class Node {
    Vec3f position;
    Vec3f rotation;
    std::string name = "";

public:
    void set_name(const std::string name);
    std::string get_name() const;

    void set_position(const Vec3f position);
    Vec3f get_position() const;

    void set_rotation(const Vec3f rotation);
    Vec3f get_rotation() const;

    Node(const std::string name="Non-name");
    virtual ~Node();
};