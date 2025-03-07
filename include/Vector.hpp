#pragma once

#include <array>
#include <type_traits>

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
