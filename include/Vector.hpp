#pragma once

#include "utils.hpp"
#include "gladiator.h"

#if 1
class Vector2 {
private:
    float _x;
    float _y;

public:
    explicit Vector2() : _x(0.), _y(0.) {}
    explicit Vector2(float x, float y) : _x(x), _y(y) {}

    float getX() const {
        return this->_x;
    }

    void setX(float x) {
        this->_x = x;
    }

    float getY() const {
        return this->_y;
    }

    void setY(float y) {
        this->_y = y;
    }

    float norm1() const {
        return ABS(_x) + ABS(_y);
    }

    float norm2() const {
        return std::sqrt(_x * _x + _y * _y);
    }

    void normalize()
    {
        this->_x /= norm2();
        this->_y /= norm2();
    }

    Vector2 normalized() const
    {
        Vector2 out = *this;
        out.normalize();
        return out;
    }

    Vector2 operator-(const Vector2 &other) const {
        return Vector2{this->_x - other._x, this->_y - other._y};
    }

    Vector2 operator+(const Vector2 &other) const {
        return Vector2{this->_x + other._x, this->_y + other._y};
    }

    Vector2 operator*(float f) const {
        return Vector2{this->_x * f, this->_y * f};
    }

    bool operator==(const Vector2 &other) const {
        return ABS(this->_x - other._x) < 1e-5 && ABS(this->_y - other._y) < 1e-5;
    }

    bool operator!=(const Vector2 &other) const {
        return !(*this == other);
    }

    float dot(const Vector2 &other) const {
        return this->_x * other._x + this->_y * other._y;
    }

    float cross(const Vector2 &other) const {
        return this->_x * other._y - this->_y * other._x;
    }

    float angle(const Vector2 &m) const {
        return std::atan2(cross(m), dot(m));
    }

    float angle() const {
        return std::atan2(this->_y, this->_x);
    }
};
#else
namespace geometry {
    template <typename T, unsigned int N>
    class Vector {
    private:
        std::array<T, N> _components;

    public:
        explicit Vector() : _components() {}
        explicit Vector(std::array<T, N> components) : _components(components) {}
        ~Vector() = default;

        T& operator[](unsigned int index) {
            return _components[index];
        }

        const T& operator[](unsigned int index) const {
            return _components[index];
        }

        float norm1() const {
            float result = 0;

            for (int i = 0; i < N; i++) {
                result += ABS(this->_components[i]);
            }
            return result;
        }

        float norm2() const {
            float result = 0;

            for (int i = 0; i < N; i++) {
                result += this->_components[i] * this->_components[i];
            }
            return std::sqrt(result);
        }

        void normalize() {
            float norm = this->norm2();

            for (int i = 0; i < N; i++) {
                this->_components[i] /= norm;
            }
        }

        const T dot(const Vector<T, N>& other) {
            T result = 0;

            for (int i = 0; i < N; i++) {
                result += this->_components[i] * other._components[i];
            }
            return result;
        }

        Vector& operator=(const Vector<T, N>& other) {
            for (int i = 0; i < N; i++) {
                this->_components[i] = other._components[i];
            }
            return *this;
        }

        bool operator==(const Vector<T, N>& other) {
            for (int i = 0; i < N; i++) {
                if (this->_components[i] != other._components[i]) {
                    return false;
                }
            }
            return true;
        }
        bool operator!=(const Vector<T, N>& other) {
            return !(*this == other);
        }

        Vector operator+(const Vector<T, N>& other) {
            Vector<T, N> result;

            for (int i = 0; i < N; i++) {
                result[i] = this->_components[i] + other._components[i];
            }
            return result;
        }
        Vector& operator+=(const Vector<T, N>& other) {
            for (int i = 0; i < N; i++) {
                this->_components[i] += other._components[i];
            }
            return *this;
        }

        Vector operator-(const Vector<T, N>& other) {
            Vector<T, N> result;

            for (int i = 0; i < N; i++) {
                result[i] = this->_components[i] - other._components[i];
            }
            return result;
        }
        Vector& operator-=(const Vector<T, N>& other) {
            for (int i = 0; i < N; i++) {
                this->_components[i] -= other._components[i];
            }
            return *this;
        }

        Vector operator*(const T& other) {
            Vector<T, N> result;

            for (int i = 0; i < N; i++) {
                result[i] = this->_components[i] * other._components[i];
            }
            return result;
        }
        Vector& operator*=(const T& other) {
            for (int i = 0; i < N; i++) {
                this->_components[i] *= other._components[i];
            }
            return *this;
        }

        Vector operator/(const T& other) {
            Vector<T, N> result;

            for (int i = 0; i < N; i++) {
                result[i] = this->_components[i] / other._components[i];
            }
            return result;
        }
        Vector& operator/=(const T& other) {
            for (int i = 0; i < N; i++) {
                this->_components[i] /= other._components[i];
            }
            return *this;
        }
    };
}
#endif
