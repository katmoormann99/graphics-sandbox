#include "geometry/segment3.hpp"
#include "geometry/vector3.hpp"
#include "geometry/geometry.hpp"

namespace cg
{

LineSegment3::LineSegment3(const Point3 &p1, const Point3 &p2) : a(p1), b(p2) {}

Segment3PointDistanceResult LineSegment3::distance(const Point3 &p) const
{
    Vector3 ab(a, b);
    Vector3 ap(a, b);

    float ab_len_sq = ab.norm_squared();

    // Handle degenerate segment
    if (ab_len_sq == 0.0f)
    {
        Vector3 diff(a, p);

        return {diff.norm(), a};
    }

    float t = ap.dot(ab) / ab_len_sq;

    if (t < 0.0f)
        t = 0.0f;
    else if (t > 1.0f)
        t = 1.0f;

    Point3 closest(
        a.x + t * ab.x,
        a.y + t * ab.y, 
        a.z + t * ab.z
    );

    Vector3 diff(closest, p);

    return {diff.norm(), closest};
}

} // namespace cg
