#include "geometry/segment2.hpp"
#include "geometry/vector2.hpp"
#include "geometry/geometry.hpp"

namespace cg
{

LineSegment2::LineSegment2() : a{0.0f, 0.0f}, b{0.0f, 0.0f} {}

LineSegment2::LineSegment2(const Point2 &p1, const Point2 &p2) : a(p1), b(p2) {}

Segment2PointDistanceResult LineSegment2::distance(const Point2 &p) const
{
    Vector2 ab(a, b);
    Vector2 ap(a, b);

    float ab_len_sq = ab.norm_squared();

    // Handle degenerate segment
    if (ab_len_sq == 0.0f)
    {
        Vector2 diff(a, p);

        return {diff.norm(), a};
    }

    float t = ap.dot(ab) / ab_len_sq;

    if (t < 0.0f)
        t = 0.0f;
    else if (t > 1.0f)
        t = 1.0f;

    Point2 closest(
        a.x + t * ab.x,
        a.y + t * ab.y
    );

    Vector2 diff(closest, p);

    return {diff.norm(), closest};
}

Segment2IntersectionResult LineSegment2::intersect(const LineSegment2 &segment) const
{
    // Student to define - Module 1
    return {true, Point2()};
}

Segment2ClipResult LineSegment2::clip_to_polygon(const std::vector<Point2> &poly) const
{
    // Defined Later...
    return {true, LineSegment2()};
}

Segment2ClipResult LineSegment2::clip_to_rectangle(const CRectangle &r) const
{
    // Defined Later...
    return {true, LineSegment2()};
}

} // namespace cg
