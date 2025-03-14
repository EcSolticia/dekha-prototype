#include "screen.h"

// ***
// Setters and getters for private member variables
// ***
void Screen::set_height(const size_t height) {
    this->height = height;
}
size_t Screen::get_height() const {
    return this->height;
}
void Screen::set_width(const size_t width) {
    this->width = width;
}
size_t Screen::get_width() const {
    return this->width;
}

void Screen::set_dimensions(Vector2 dimensions) {
    this->dimensions = dimensions;
}
Vector2 Screen::get_dimensions() const{
    return this->dimensions;
}

void Screen::set_origin(const size_t x, const size_t y) {
    // The origin is represented w.r.t. the relative coordinates
    this->origin_x = x;
    this->origin_y = y;
}

void Screen::set_cam(Camera* const cam_node) {
    this->cam = cam_node;
}
Camera* Screen::get_cam() const {
    return this->cam;
}

// ***
// Transformation functions
// ***
size_t Screen::get_idx_from_relcartesian(const size_t x, const size_t y) const {
    /*
        Let f(x, y) = idx
        If y = 0, then f(x, y) = f(x, 0) = x
        If x = 0, then f(x, y) = f(0, y) = width * y
        Since f(x, y) is a linear function of, it follows that 

            f(x, y) = x + width * y 

        Domain of x and y: [0, width] and [0, height], respectively
        Range of x and y: x * y - 1
    */
    bool is_in_domain = (0 <= x <= width) and (0 <= y <= height);
    if (!is_in_domain) {
        throw std::domain_error("Negative or large relcartesian input");
    }

    return (x + width * y);
}

Vector2 Screen::get_cartesian_from_relcartesian(const size_t x, const size_t y) const {
    int cx = (size_t)(x - origin_x);
    int cy = (size_t)(origin_y - y);
    return Vector2(cx, cy);
}

Vector2 Screen::map_vertex_to_screen(Vector3 vertex_pos) const {
    Vector2 mapped;
    
    Vector2 dim = this->get_dimensions();
    mapped.x = (vertex_pos.x * dim.x)/(vertex_pos.z * this->get_width());
    mapped.y = (vertex_pos.y * dim.y)/(vertex_pos.z * this->get_height());

    return mapped;
}

// ***
// Functions for interacting with the `data` variable
// ***
void Screen::set_data(Vector2 at, const char value) {
    size_t idx = this->get_idx_from_relcartesian(at.x, at.y);
    this->data[idx] = value;
}

void Screen::draw_point(Vector2 at) {
    this->set_data(at, '*');
}
void Screen::draw_line(Vector2 from, Vector2 to) {
    Vector2 diff = from - to;
    double l = diff.length();
    Vector2 unit_diff = diff/l;
    size_t l_rounded  = (size_t) l;
    for (size_t i = 0; i < l_rounded; ++i) {
        Vector2 current = from + unit_diff * i;
        draw_point(current);
    }
}

void Screen::draw_vertex(Vector3 at) {
    Vector2 at2d = this->map_vertex_to_screen(at);
    draw_point(at2d);
}
void Screen::draw_line(Vector3 from, Vector3 to) {
    Vector2 from2d = map_vertex_to_screen(from);
    Vector2 to2d = map_vertex_to_screen(to);

    draw_line(from2d, to2d);
}


// Boolean functions

// Assumes origin = Vector2()
bool Screen::is_point_in_triangle(Vector2 P, Vector2 A, Vector2 B) const {
    double det = (A.x * B.y - B.x * A.y);
    double w_1 = (P.x * B.y - P.y * B.x)/det;
    double w_2 = (A.x * P.y - P.x * A.y)/det;

    bool c1 = (w_1 + w_2 <= 1);
    bool c2 = (w_1 >= 0 and w_2 >= 0);
    return (c1 and c2);
}

// The input parameter must represent a triangular face
void Screen::draw_triangle_face(std::vector<Vector3> triangle_data) {
    if (triangle_data.size() != 3) {
        throw std::domain_error("Passed argument does not correspond to a triangle");
    }

    // All vertices of the triangle as mapped to the screen
    Vector2 A = this->map_vertex_to_screen(triangle_data[0]);
    Vector2 B = this->map_vertex_to_screen(triangle_data[1]);
    Vector2 C = this->map_vertex_to_screen(triangle_data[2]);

    // The vertices if A is assumed to be the origin
    Vector2 P = B - A;
    Vector2 Q = C - A;

    // Bounding rectangle calculation
    Vector2 bottom_right = get_bounding_rect_bottomright(A, B, C);
    Vector2 top_left = get_bounding_rect_topleft(A, B, C);


    int i = (int) top_left.x; // left
    int l = (int) bottom_right.x; // right
    while (i < l) { // left to right

        int j = (int) bottom_right.y; // bottom
        int m = (int) top_left.y; // top
        while (j < m) { // bottom to top
            
            // Get the position vector of the potential pixel
            Vector2 X = Vector2((double)i, (double)j);
            
            // Draw if it is within the triangle
            if (this->is_point_in_triangle(X, P, Q)) {
                this->draw_point(X);
            }

            ++j; // bottom to top
        }

        ++i; // left to right
    }
}


// **
// The Constructor and Destructor
// **
Screen::Screen(const size_t height, const size_t width, Vector2 dimensions) {
    this->set_height(height);
    this->set_width(width);
    this->set_dimensions(dimensions);

    this->initialize();

    std::cout << "Screen of size (" << width << ", " << height << ") constructed" << std::endl;
}
Screen::~Screen() {

    std::cout << "Screen desctructed" << std::endl; 
}