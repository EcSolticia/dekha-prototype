#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <array>
#include "common/types.h"
#include "common/math.h"
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
        Vector2 get_relcartesian_from_idx(size_t idx) {
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
            
            return Vector2(rel_x, rel_y);
        }
        
    public:
        Vector2 map_vertex_to_screen(Vector3 vertex_position) {
            // position on screen
            Vector2 PoS;
        
            if (vertex_position.z == 0) {
                throw std::domain_error("Error in mapping vertex to screen: division by zero");
            }
        
            Vector2 cam_dim = (this->get_cam())->get_dimensions();
            PoS.x = (vertex_position.x * width)/(vertex_position.z * cam_dim.x);
            PoS.y = (vertex_position.y * height)/(vertex_position.z * cam_dim.y);
        
            std::cout << "Mapped " << vertex_position << " to " << PoS << std::endl;

            return PoS;
        }
        void draw_vertex(Vector3 vertex_position) {
            Vector2 PoS = this->map_vertex_to_screen(vertex_position);
            
            this->set_pixel((int)(PoS.x), (int)(PoS.y));
        }
        void draw_3dline(Vector3 from, Vector3 to) {
            if (from == to) {
                return;
            }
            Vector2 A = this->map_vertex_to_screen(from);
            Vector2 B = this->map_vertex_to_screen(to);

            draw_line(A, B);
        }

        void draw_triangle_face(std::vector<Vector3> triangle_data) {
            if (triangle_data.size() != 3)  {
                throw std::domain_error("Passed argument isn't a triangle");
            }

            Vector3 a = triangle_data[0];
            Vector3 b = triangle_data[1];
            Vector3 c = triangle_data[2];

            Vector2 A = this->map_vertex_to_screen(a);
            Vector2 B = this->map_vertex_to_screen(b);
            Vector2 C = this->map_vertex_to_screen(c);

            Vector2 P = B - A;
            double lP = P.length();
            Vector2 Q = C - A;
            double lQ = Q.length();

            // calculate bounding region
            Vector2 top_left = {min(A.x, B.x, C.x), max(A.y, B.y, C.y)};
            Vector2 bottom_right = {max(A.x, B.x, C.x), min(A.y, B.y, C.y)};

            size_t i = bottom_right.y;
            size_t l = top_left.y;
            while (i < l) {
                
                size_t p = top_left.x;
                size_t q = bottom_right.x;
                while (p < q) {

                    // check if (p, i) is in the triangle
                    Vector2 X = {(double)(p - top_left.x), (double)(i - bottom_right.y)};
                    double l = X.length();
                    double w_p = (X.x * Q.y - X.y * Q.x)/(P.x * Q.y - P.y * Q.x);
                    double w_q = (P.x * X.y - X.x * P.y)/(P.x * Q.y - P.y * Q.x);

                    if (w_p + w_q <= 1 and w_p >= 0 and w_q >= 0) {
                        // fill pixel
                        set_pixel(p, i, 1);
                    } else {
                        std::cout << "Pixel " << X << " out of face" << std::endl;
                    }

                    ++p;
                }

                ++i;
            }
        }

        void draw_polygon(Polygon* polygon_node) {
            std::vector<Vector3> data = polygon_node->get_data();

            size_t l = data.size();
            if (l < 3) {
                throw std::domain_error("Passed Polygon node doesn't contain sufficient number of data points!");
            }
            
            // draw wireframe
            for (size_t i = 0; i < l - 1; ++i) {
                this->draw_3dline(data[i], data[i + 1]);
            }
            this->draw_3dline(data[l - 1], data[0]);
        }
        void draw_polygonX(Polygon* polygon_node) {
            std::vector <Vector3> data = polygon_node->get_data();

            size_t l = data.size();
            if (l < 3) {
                throw std::domain_error("Passed Polygon node doesn't contain sufficient number of data points!");
            }

            for (size_t i = 0; i < l; ++i) {
                for (size_t j = i; j < l; ++j) {
                    this->draw_3dline(data[i], data[j]);
                }
            }
        }
        // incomplete
        void draw_polygon_with_faces(Polygon* polygon_node) {
            std::vector <Vector3> data = polygon_node->get_data();

            size_t l = data.size();
            if (l < 3) {
                throw std::domain_error("Passed Polygon node doesn't contain sufficient number of data points!");
            }

        }

        Camera* get_cam() const {
            if (this->cam == nullptr) {
                throw std::runtime_error("Screen camera not yet set");
            }
            return this->cam;
        }
        void set_cam(Camera* cam) {
            std::cout << "Setting screen camera to " << cam << std::endl;
            this->cam = cam;
        }

        Vector2 get_pixel_dimensions() {
            return Vector2(width, height);
        }

        void set_pixel(int x, int y, int val) {
            data[get_idx_from_cartesian(x, y)] = val;
            std::cout << "Set pixel (" << x << ", " << y << ") to value " << val << std::endl;
        }
    
        void draw_line(Vector2 A, Vector2 B) {
            Vector2 diff = B - A;
            double l = diff.length();
            Vector2 unit_diff = diff/l;
            size_t lui = (size_t) l;
            for (size_t i = 0; i < lui; ++i) {
                //Vec2f Apda = add(A, multiply(unit_diff, i));
                Vector2 current = A + unit_diff * i;

                set_pixel((int)(current.x), (int)(current.y), 1);

            }
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