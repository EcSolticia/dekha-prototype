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
            /*
            Each increment of `y` corresponds to one additional factor of `width` being added
            to the index.
            The value of `x` directly adds to the index.
            Therefore, index is `y * width + x`.
            */
        }
    
        size_t get_idx_from_cartesian(const int x, const int y) {
            // calculate prospective relative coordinates
            int a = x + (int)(origin_x);
            int b = (int)(origin_y) - y;

            // check if the prospectives are above the lower bounds
            bool valid1 = (a >= 0 and b >= 0);
            
            // type conversions
            size_t rel_x = (size_t)(a);
            size_t rel_y = (size_t)(b);
    
            // check if the prospectives are below the upper bounds
            bool valid2 = (a < width and b < height);

            // the actual "check"
            // an out_of_range error if either of the relative coordinates is out of bounds
            if (!(valid1 and valid2)) {
                std::string msg = "Coordinates (" + std::to_string(x) + ", " + std::to_string(y) + ") out of range.";
                throw std::out_of_range(msg);
            }
    
            // this block is executed iff the relative coordinates calculated are valid
            return get_idx_from_relcartesian(rel_x, rel_y);
        }
        Vec2f get_cartesian_from_idx(size_t idx) {
            if (idx >= height * width) {
                std::string msg = "Index " + std::to_string(idx) + " out of range";
                throw std::out_of_range(msg);
            }
    
            /*
            index = y * width + x;
            Thus, index % width = 0 + x % width = x.
            As well as index/width = y + x/width. Thus, the floor is y.
            */

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
                std::string msg = "Error in mapping vertex to screen: division by zero";
                throw std::domain_error(msg);
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
                std::string msg = "Passed Polygon node doesn't contain sufficient number of data points!";
                throw std::runtime_error(msg);
            }
            
            for (size_t i = 0; i < l - 1; ++i) {
                this->draw_3dline(data[i], data[i + 1]);
            }
            this->draw_3dline(data[l - 1], data[0]);
        }

        Camera* get_cam() const {
            if (this->cam == nullptr) {
                std::string msg = "Screen camera not yet set";
                throw std::runtime_error(msg);
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