#pragma once
#include <iostream>
#include <string>
#include "../common/types.h"

class Node {
    Vector3 position;
    Vector3 rotation;
    std::string name = "";

public:
    void set_name(const std::string name);
    std::string get_name() const;

    void set_position(const Vector3 position);
    Vector3 get_position() const;

    void set_rotation(const Vector3 rotation);
    Vector3 get_rotation() const;

    Node(const std::string name="Non-name");
    virtual ~Node();
};