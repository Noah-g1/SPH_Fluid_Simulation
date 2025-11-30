//
// Created by Noah Graff on 11/29/25.
//

#ifndef SPH_FLUID_SIMULATION_VECTOR2_H
#define SPH_FLUID_SIMULATION_VECTOR2_H
#include <cmath>
#include <format>
#include <stdexcept>
#include <string>
#include <utility>

struct Vector2 {
    float x, y;

    constexpr Vector2(const float x = 0.0f, const float y = 0.0f) : x(x), y(y) {}

    [[nodiscard]]
    float magnitude() const noexcept {
        return std::sqrt(x * x + y * y);
    }

    [[nodiscard]]
    float dot(const Vector2& other) const noexcept {
        return x * other.x + y * other.y;
    }

    [[nodiscard]]
    float cross(const Vector2& other) const noexcept {
        return x * other.y - y * other.x;
    }

    [[nodiscard]]
    Vector2 normalize() const noexcept {
        const float mag = magnitude();

        if (mag == 0) {
            return {0, 0};
        }

        return {x / mag, y / mag};
    }

    [[nodiscard]]
    constexpr Vector2 operator+ (const Vector2& toAdd) const noexcept {
        return {x + toAdd.x, y + toAdd.y};
    }

    void operator+= (const Vector2& toAdd) noexcept {
        x += toAdd.x;
        y += toAdd.y;
    }

    [[nodiscard]]
    constexpr Vector2 operator- (const Vector2& toSubtract) const noexcept {
        return {x - toSubtract.x, y - toSubtract.y};
    }

    void operator-= (const Vector2& toSubtract) noexcept {
        x -= toSubtract.x;
        y -= toSubtract.y;
    }

    [[nodiscard]]
    constexpr Vector2 operator* (const Vector2& toMultiply) const noexcept {
        return {x * toMultiply.x, y * toMultiply.y};
    }

    [[nodiscard]]
    constexpr Vector2 operator* (float toMultiply) const noexcept {
        return {x * toMultiply, y * toMultiply};
    }

    void operator*= (const Vector2& toMultiply) noexcept {
        x *= toMultiply.x;
        y *= toMultiply.y;
    }

    void operator*= (float toMultiply) noexcept {
        x *= toMultiply;
        y *= toMultiply;
    }

    [[nodiscard]]
     Vector2 operator/ (const Vector2& toDivide) const {
        if (toDivide.x == 0 || toDivide.y == 0) {
            throw std::runtime_error("Division by zero is not allowed.");
        }

        return {x / toDivide.x, y / toDivide.y};
    }

    [[nodiscard]]
     Vector2 operator/ (float toDivide) const {
        if (toDivide == 0) {
            throw std::runtime_error("Division by zero is not allowed.");
        }

        return {x / toDivide, y / toDivide};
    }

    void operator/= (const Vector2& toDivide) {
        if (toDivide.x == 0 || toDivide.y == 0) {
            throw std::runtime_error("Division by zero is not allowed.");
        }

        x /= toDivide.x;
        y /= toDivide.y;
    }

    void operator/= (float toDivide) {
        if (toDivide == 0.0f) {
            throw std::runtime_error("Division by zero is not allowed.");
        }

        x /= toDivide;
        y /= toDivide;
    }

    [[nodiscard]]
    bool operator== (const Vector2& other) const {
        constexpr float eps = 1e-6f;
        return std::fabs(x - other.x) < eps &&
               std::fabs(y - other.y) < eps;
    }

    [[nodiscard]]
    bool operator!= (const Vector2& other) const {
        return !(*this == other);
    }

    static constexpr Vector2 zero() noexcept {
        return {0, 0};
    }

    static constexpr Vector2 one() noexcept {
        return {1, 1};
    }

    static constexpr Vector2 left() noexcept {
        return {-1, 0};
    }

    static constexpr Vector2 right() noexcept {
        return {1, 0};
    }

    static constexpr Vector2 up() noexcept {
        return {0, 1};
    }

    static constexpr Vector2 down() noexcept {
        return {0, -1};
    }

    std::string toString() {
        return std::format("({}, {})", x, y);
    }
};

#endif //SPH_FLUID_SIMULATION_VECTOR2_H