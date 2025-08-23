#include "bits/stdc++.h"
namespace GEOM {

template <typename T> class Vector2D {
  public:
    T x, y;

    Vector2D() : x(), y() {}
    Vector2D(T x, T y) : x(x), y(y) {}

    constexpr Vector2D operator+(const Vector2D& other) const { return {x + other.x, y + other.y}; }
    constexpr Vector2D operator-(const Vector2D& other) const { return {x - other.x, y - other.y}; }
    constexpr Vector2D operator*(const T scalar) const { return {x * scalar, y * scalar}; };
    constexpr Vector2D operator/(const T scalar) const { return {x / scalar, y / scalar}; };

    constexpr bool operator==(const Vector2D& other) const { return x == other.x && y == other.y; }
    constexpr bool operator!=(const Vector2D& other) const { return !(*this == other); }

    constexpr T dot(const Vector2D& other) const { return x * other.x + y * other.y; }
    constexpr T cross(const Vector2D& other) const { return x * other.y - y * other.x; }
    constexpr T norm2_sq() const { return x * x + y * y; }
    constexpr T norm2() const { return std::sqrt(norm2()); }

    constexpr static T distance(const Vector2D& a, const Vector2D& b) { return (a - b).norm2(); }

    constexpr friend std::ostream& operator<<(std::ostream& os, const Vector2D& p) {
        os << '(' << p.x << ", " << p.y << ')';
        return os;
    }
};

}; // namespace GEOM
