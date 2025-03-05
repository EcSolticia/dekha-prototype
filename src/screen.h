#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <array>
#include "common/types.h"

template <size_t height, size_t width> class Screen {
    private:
        std::array<size_t, height * width> data;
        size_t origin_x;
        size_t origin_y;

        size_t get_idx_from_relcartesian(const size_t x, const size_t y) {
            return y * width + x;
        }
    
        size_t get_idx_from_cartesian(const int x, const int y) {
            size_t rel_x = x + origin_x;
            size_t rel_y = origin_y - y;
    
            if (rel_x >= width or rel_y >= height) {
                std::cerr << "Coordinates (" << x << ", " << y << ") out of range" << std::endl;
                throw -1;
            }
    
            return get_idx_from_relcartesian(rel_x, rel_y);
        }
        Vec2f get_cartesian_from_idx(size_t idx) {
            if (idx >= height * width) {
                std::cerr << "Index " << idx << " out of range" << std::endl;
                throw -1;
            }
    
            size_t rel_x = idx % width;
            size_t rel_y = floor(idx/width);
    
            Vec2f res = {rel_x, rel_y};
            return res;
        }
        
    public:
        void set_pixel(int x, int y, int val) {
            data[get_idx_from_cartesian(x, y)] = val;
            std::cout << "Set pixel (" << x << ", " << y << ") to value " << val << std::endl;
        }
    
        void draw_line(Vec2f A, Vec2f B) {
            Vec2f diff = subtract(B, A);
            cout_vecf("Calculated diff as ", diff, "");
            double l = length(diff);
            std::cout << "Calculated length as " << l << "\n";
            Vec2f unit_diff = divide(diff, l);
            cout_vecf("Calculated unit_diff as ", unit_diff, "");
            size_t lui = (size_t) l;
            std::cout << "Calculated lui as " << lui << "\n";
            for (size_t i = 0; i < lui; ++i) {
                Vec2f Apda = add(A, multiply(unit_diff, i));
                cout_vecf("Calculated Apda", Apda, "");
                
                int x = (int) Apda[0];
                int y = (int) Apda[1];

                set_pixel(x, y, 1);

            }
            std::cout << std::endl;
        }

        void output_display() {
            std::cout << "Outputting display...\n\n";

            size_t xi = 0;
            size_t yi = 0;
            while (yi < height) {
                std::string line;
                line.resize(width);
                
                xi = 0;
                while (xi < width) {
                    
                    size_t idx = get_idx_from_relcartesian(xi, yi);

                    if (data[idx] == 1) {
                        line[xi] = '#';
                    } else {
                        line[xi] = '-';
                    }

                    ++xi;
                }
                std::cout << line << "\n";
                
                ++yi;
            }
            std::cout << std::endl;
        }

        void initialize_data() {
            for (size_t i = 0; i < height*width; ++i) {
                data[i] = '-';
            }
        }

        Screen(size_t origin_x, size_t origin_y) {
            this->origin_x = origin_x;
            this->origin_y = origin_y;
            std::cout << "Screen of size [" << width << ", " << height << "] and ";
            std::cout << "origin [" << origin_x << ", " << origin_y << "] constructed" << std::endl;
            initialize_data();
        }
        ~Screen() {
            std::cout << "Screen desctructed" << std::endl;
        }
    };