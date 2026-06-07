#include "geometry/vector2.hpp"

#include "geometry/geometry.hpp"

#include <cmath>

namespace cg
{

Vector2::Vector2() : x(0.0f), y(0.0f) {}

Vector2::Vector2(const Point2 &p) : x(p.x), y(p.y) {}

Vector2::Vector2(float ix, float iy) : x(ix), y(iy) {}

Vector2::Vector2(const Point2 &from, const Point2 &to) : x(to.x - from.x), y(to.y - from.y) {}

Vector2::Vector2(const Vector2 &w) : x(w.x), y(w.y) {}

Vector2 &Vector2::operator=(const Vector2 &w)
{
    x = w.x;
    y = w.y;
    return *this;
}

void Vector2::set(float ix, float iy)
{
    x = ix;
    y = iy;
}

void Vector2::set(const Point2 &p)
{
    x = p.x;
    y = p.y;
}

void Vector2::set(const Point2 &from, const Point2 &to)
{
    x = to.x - from.x;
    y = to.y - from.y;
}

Vector2 Vector2::operator+(const Vector2 &w) const { return Vector2(x + w.x, y + w.y); }

Vector2 &Vector2::operator+=(const Vector2 &w)
{
    x += w.x;
    y += w.y;
    return *this;
}

Vector2 Vector2::operator-(const Vector2 &w) const { return Vector2(x - w.x, y - w.y); }

Vector2 &Vector2::operator-=(const Vector2 &w)
{
    x -= w.x;
    y -= w.y;
    return *this;
}

Vector2 Vector2::operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }

Vector2 &Vector2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

bool Vector2::operator==(const Vector2 &w) const { return (x == w.x && y == w.y); }

float Vector2::dot(const Vector2 &w) const
{
    // Compute the dot product between the current vector (x, y) and 
    // another vector named 'w' (w.x, w.y)
    // AxBx + AyBy
    return x * w.x + y * w.y;
}

float Vector2::cross(const Vector2 &w) const
{
    // AxBy - AyBx
    return x * w.y - y * w.x;
}

Vector2 Vector2::get_perpendicular(bool clockwise) const
{
    // clockwise = (y, -x)
    // counter cw = (-y, x)
    if (clockwise)
        return Vector2(y, -x);
    
    // counter clockwise
    return Vector2(-y, x);
}

float Vector2::norm() const
{
    // sqrt(x^2 + y^2)
    return std::sqrt(norm_squared());
}

float Vector2::norm_squared() const
{
    // x^2 + y^2
    return x * x + y * y;
}

Vector2 &Vector2::normalize()
{
    // (x/|v|, y/|v|)
    float n = norm();
    if (n != 0.0f){
        x/=n;
        y/=n;
    }
    return *this;
}

float Vector2::component(const Vector2 &w) const
{
    // component of A along B
    // = (A dot B) / |B|
    float n = w.norm();

    if (n == 0.0f)
        return 0.0f;
    
    return dot(w)/n;
}

Vector2 Vector2::projection(const Vector2 &w) const
{
    // vector projection of A onto B
    // = ((A dot B) / |B|^2) * B
    
    float nsq = w.norm_squared();
    if (nsq == 0.0f)
        return Vector2();

    return w * (dot(w) / nsq);
}

float Vector2::angle_between(const Vector2 &w) const
{
    // theta = acos((A dot B) / (|A||B|))

    float denom = norm() * w.norm();

    if (denom == 0.0f)
        return 0.0f;

    float c = dot(w) / denom;

    // clamp because floating point math can slightly exceed [-1, 1]
    if (c > 1.0f) c = 1.0f;
    if (c < -1.0f) c = -1.0f;
    
    return std::acos(c);
}

Vector2 Vector2::reflect(const Vector2 &normal) const
{
    // reflection formula:
    // R = V - 2(V dot N)N
    Vector2 n = normal;
    n.normalize();

    return *this - 2.0f * dot(n) * n;
}

Vector2 operator*(float s, const Vector2 &v) { return Vector2(v.x * s, v.y * s); }

} // namespace cg
