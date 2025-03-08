#pragma once

#include <iostream>
#include <cmath>

struct Vector2 {
    double x;
    double y;

    Vector2 operator+(const Vector2& addend) {
        return Vector2(this->x + addend.x, this->y + addend.y);
    }

    Vector2 operator-(const Vector2& subtrahend) {
        return Vector2(this->x - subtrahend.x, this->y - subtrahend.y);
    }

    Vector2 operator*(double factor) {
        return Vector2(this->x * factor, this->y * factor);
    }

    Vector2 operator/(double divisor) {
        if (divisor == 0) {
            throw std::domain_error("Divison by zero!");
        }
        return Vector2(this->x / divisor, this->y / divisor);
    }

    // dot product
    double operator*(const Vector2& factor) {
        return this->x * factor.x + this->y * factor.y;
    }

    bool operator==(const Vector2& to) {
        return (this->x == to.x and this->y == to.y);   
    }

    double length() {
        return sqrt(pow(this->x, 2) + pow(this->y, 2));
    }
  
    Vector2(void) {
        this->x = 0;
        this->y = 0;
    }
    Vector2(double x, double y) {
        this->x = x;
        this->y = y;
    } 
};
inline std::ostream& operator<<(std::ostream& stream, const Vector2& vec) {
    stream << vec.x << ", " << vec.y;
    return stream;
}

struct Vector3 {
    double x;
    double y;
    double z;

    Vector3 operator+(const Vector3& addend) {
        return Vector3(this->x + addend.x, this->y + addend.y, this->z + addend.z);
    }

    Vector3 operator-(const Vector3& subtrahend) {
        return Vector3(this->x - subtrahend.x, this->y - subtrahend.y, this->z - subtrahend.z);
    }

    Vector3 operator*(double factor) {
        return Vector3(this->x * factor, this->y * factor, this->z * factor);
    }

    Vector3 operator/(double divisor) {
        if (divisor == 0) {
            throw std::domain_error("Division by zero!");
        }
        return Vector3(this->x / divisor, this->y / divisor, this->z / divisor);
    }

    // dot product
    double operator*(const Vector3& factor) {
        return this->x * factor.x + this->y * factor.y + this->z * factor.z;
    }

    bool operator==(const Vector3& to) {
        return (this->x == to.x and this->y == to.y and this->z == to.z);
    }

    double length() {
        return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
    }
  
    Vector3(void) {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    Vector3(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    } 
};
inline std::ostream& operator<<(std::ostream& stream, const Vector3& vec3) {
    stream << vec3.x << ", " << vec3.y << ", " << vec3.z;
    return stream;
}