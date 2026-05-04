#include "geometry/plane.hpp"

#include "geometry/geometry.hpp"

#include <cmath>

namespace cg
{

Plane::Plane() : a(0.0f), b(0.0f), c(0.0f), d(0.0f) {}

Plane::Plane(const Point3 &p, const Vector3 &n) { set(p, n); }

Plane::Plane(const Point3 &p1, const Point3 &p2, const Point3 &p3)
{
    // Student to define - Module 1
}

void Plane::set(const Point3 &p, const Vector3 &n)
{
    // Student to define - Module 1
}

void Plane::normalize()
{
    // Student to define - Module 1
}

float Plane::solve(const Point3 &p) const
{
    // Student to define - Module 1
    return 0.0f;
}

Vector3 Plane::get_normal() const
{
    // Student to define - Module 1
    return Vector3();
}

} // namespace cg
