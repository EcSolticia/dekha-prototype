#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <array>
#include "common/types.h"
#include "common/math.h"
#include "node/camera.h"

class Screen {
    private:
        std::vector<char> data;

        Camera* cam = nullptr;

        // The height and width of the screen in projected space
        size_t height;
        size_t width;

        // The dimensions of the "screen" as a rectangular section of
        // a plane in 3d space
        Vector2 dimensions;
        
        size_t origin_x;
        size_t origin_y;

        // Initialization function (separate from the construction)
        void initialize() {
            size_t l = height * width;
            data.resize(l);
            for (size_t i = 0; i < l; ++i) {
                data[i] = '-';
            }
        }

    public:
        // **
        // Setters and getters for private member variables
        // **
        void set_height(const size_t height);
        size_t get_height() const;
        void set_width(const size_t width);
        size_t get_width() const;
        
        void set_dimensions(Vector2 dimensions);
        Vector2 get_dimensions() const;

        void set_origin(const size_t x, const size_t y);

        void set_cam(Camera* const cam_node);
        Camera* get_cam() const;

        // **
        // Transformation functions
        // **
        size_t get_idx_from_relcartesian(const size_t x, const size_t y) const;
        Vector2 get_cartesian_from_relcartesian(const size_t x, const size_t y) const;

        Vector2 map_vertex_to_screen(Vector3 vertex_pos) const;

        // **
        // Functions for interacting with the `data` variable
        // **
        void set_data(Vector2 at, const char value);

        // 2D Draw functions
        void draw_point(Vector2 at);
        void draw_line(Vector2 from, Vector2 to);
        
        // 3D Draw functions
        void draw_vertex(Vector3 at);
        void draw_line(Vector3 from, Vector3 to);
        
        void draw_triangle_face(std::vector<Vector3> triangle_data);

        // Booleans
        bool is_point_in_triangle(Vector2 P, Vector2 A, Vector2 B) const;

        // **
        // The Constructor and Destructor
        // **
        Screen(const size_t height, const size_t width);
        ~Screen();
};