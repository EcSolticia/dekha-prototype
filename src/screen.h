#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <array>
#include "common/types.h"
#include "node/camera.h"

template <size_t height, size_t width> class Screen {
    private:
        // It's easier to connect the camera to the screen than the other way around
        Camera* cam = nullptr;
    
        std::array<size_t, height * width> data;
        size_t origin_x;
        size_t origin_y;

        size_t get_idx_from_relcartesian(const size_t x, const size_t y) {
            return y * width + x;
        }
    
        size_t get_idx_from_cartesian(const int x, const int y) {
            bool valid1 = (x + origin_x >= 0 and y + origin_y >= 0);
            size_t rel_x = x + origin_x;
            size_t rel_y = origin_y - y;
    
            bool valid2 = (rel_x < width or rel_y < height);
            if (!(valid1 and valid2)) {
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
        Vec2f map_vertex_to_screen(Vec3f vertex_position) {
            // position on screen
            Vec2f PoS;
        
            if (vertex_position[2] == 0) {
                cout_vecf<3, true>("\nVertex position", vertex_position, "");
                std::cout << "Error in mapping vertex to screen:\n";
                std::cout << "Division by zero" << std::endl;
                throw -2;
            }
        
            Vec2f cam_dim = (this->get_cam())->get_dimensions();
            PoS[0] = (vertex_position[0] * width)/(vertex_position[2] * cam_dim[0]);
            PoS[1] = (vertex_position[1] * height)/(vertex_position[2] * cam_dim[1]);
        
            cout_vecf<3, false>("Mapped", vertex_position, " to");    
            cout_vecf<2, true>("", PoS, "");

            return PoS;
        }
        void draw_vertex(Vec3f vertex_position) {
            Vec2f PoS = this->map_vertex_to_screen(vertex_position);
        
            int x = (int) PoS[0];
            int y = (int) PoS[1];
        
            this->set_pixel(x, y, 1);
        }
        void draw_3dline(Vec3f from, Vec3f to) {
            if (from == to) {
                return;
            }
            Vec2f A = this->map_vertex_to_screen(from);
            Vec2f B = this->map_vertex_to_screen(to);

            draw_line(A, B);
        }
        void draw_polygon(Polygon* polygon_node) {
            std::vector<Vec3f> data = polygon_node->get_data();

            size_t l = data.size();
            if (l < 3) {
                std::cout << "Passed Polygon node doesn't contain sufficient data points" << std::endl;
                throw -2;
            }
            
            for (size_t i = 0; i < l - 1; ++i) {
                this->draw_3dline(data[i], data[i + 1]);
            }
            this->draw_3dline(data[l - 1], data[0]);
        }

        Camera* get_cam() const {
            if (this->cam == nullptr) {
                std::cout << "Screen camera not yet set" << std::endl;
                throw -2;
            }
            return this->cam;
        }
        void set_cam(Camera* cam) {
            std::cout << "Setting screen camera to " << cam << std::endl;
            this->cam = cam;
        }

        Vec2f get_pixel_dimensions() {
            Vec2f C;
            C[0] = width;
            C[1] = height;
            return C;
        }

        void set_pixel(int x, int y, int val) {
            data[get_idx_from_cartesian(x, y)] = val;
            std::cout << "Set pixel (" << x << ", " << y << ") to value " << val << std::endl;
        }
    
        void draw_line(Vec2f A, Vec2f B) {
            Vec2f diff = subtract(B, A);
            cout_vecf<2, true>("Calculated diff as ", diff, "");
            double l = length(diff);
            std::cout << "Calculated length as " << l << "\n";
            Vec2f unit_diff = divide(diff, l);
            cout_vecf<2, true>("Calculated unit_diff as ", unit_diff, "");
            size_t lui = (size_t) l;
            std::cout << "Calculated lui as " << lui << "\n";
            for (size_t i = 0; i < lui; ++i) {
                Vec2f Apda = add(A, multiply(unit_diff, i));
                cout_vecf<2, true>("Calculated Apda", Apda, "");
                
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