#pragma once

#include <iostream>
#include <array>
#include "common/types.h"

template <size_t height, size_t width> class Screen {
    private:
        std::array<size_t, height * width> data;
        size_t origin_x;
        size_t origin_y;
    
        size_t get_idx_from_cartesian(const int x, const int y) {
            size_t rel_x = x + origin_x;
            size_t rel_y = origin_y - y;
    
            if (rel_x >= width or rel_y >= height) {
                std::cerr << "Coordinates (" << x << ", " << y << ") out of range" << std::endl;
                throw -1;
            }
    
            return rel_y * width + rel_x;
        }
        Vec2 get_cartesian_from_idx(size_t idx) {
            if (idx >= height * width) {
                std::cerr << "Index " << idx << " out of range" << std::endl;
                throw -1;
            }
    
            size_t rel_x = idx % width;
            size_t rel_y = idx/width;
    
            Vec2 res = {rel_x, rel_y};
            return res;
        }
        
    public:
        void set_pixel(int x, int y, int val) {
            data[get_idx_from_cartesian(x, y)] = val;
            std::cout << "Set pixel (" << x << ", " << y << ") to value " << val << std::endl;
        }
    
        Screen(size_t origin_x, size_t origin_y) {
            this->origin_x = origin_x;
            this->origin_y = origin_y;
            std::cout << "Screen of size [" << width << ", " << height << "] and ";
            std::cout << "origin [" << origin_x << ", " << origin_y << "] constructed" << std::endl;
        }
        ~Screen() {
            std::cout << "Screen desctructed" << std::endl;
        }
    };