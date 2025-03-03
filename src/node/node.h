#pragma once
#include <iostream>
#include "../common/types.h"

class Node {
    Vec3f position;
    Vec3f rotation;

public:
    void set_position(const Vec3f position_p);
    Vec3f get_position() const;

    void set_rotation(const Vec3f rotation_p);
    Vec3f get_rotation() const;

    Node();
    virtual ~Node();
};