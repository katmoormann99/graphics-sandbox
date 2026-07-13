// Modified by Kat Moormann Sun Sept 21 2025
// Completed the "student to define" sections in Matrix4x4
// to support modeling transformations and vector/point operations

#include "geometry/matrix.hpp"
#include "geometry/geometry.hpp"
#include <cmath>

namespace cg
{

// Forward declare logging function
void logmsg(const char *message, ...);

Matrix4x4::Matrix4x4() { set_identity(); }

void Matrix4x4::set_identity()
{
    a_[0] = 1.0f;
    a_[4] = 0.0f;
    a_[8] = 0.0f;
    a_[12] = 0.0f;
    a_[1] = 0.0f;
    a_[5] = 1.0f;
    a_[9] = 0.0f;
    a_[13] = 0.0f;
    a_[2] = 0.0f;
    a_[6] = 0.0f;
    a_[10] = 1.0f;
    a_[14] = 0.0f;
    a_[3] = 0.0f;
    a_[7] = 0.0f;
    a_[11] = 0.0f;
    a_[15] = 1.0f;
}

Matrix4x4::Matrix4x4(const Matrix4x4 &n)
{
    m00() = n.m00();
    m01() = n.m01();
    m02() = n.m02();
    m03() = n.m03();
    m10() = n.m10();
    m11() = n.m11();
    m12() = n.m12();
    m13() = n.m13();
    m20() = n.m20();
    m21() = n.m21();
    m22() = n.m22();
    m23() = n.m23();
    m30() = n.m30();
    m31() = n.m31();
    m32() = n.m32();
    m33() = n.m33();
}

Matrix4x4 &Matrix4x4::operator=(const Matrix4x4 &n)
{
    m00() = n.m00();
    m01() = n.m01();
    m02() = n.m02();
    m03() = n.m03();
    m10() = n.m10();
    m11() = n.m11();
    m12() = n.m12();
    m13() = n.m13();
    m20() = n.m20();
    m21() = n.m21();
    m22() = n.m22();
    m23() = n.m23();
    m30() = n.m30();
    m31() = n.m31();
    m32() = n.m32();
    m33() = n.m33();
    return *this;
}

bool Matrix4x4::operator==(const Matrix4x4 &n) const
{
    return (m00() == n.m00() && m01() == n.m01() && m02() == n.m02() && m03() == n.m03() &&
            m10() == n.m10() && m11() == n.m11() && m12() == n.m12() && m13() == n.m13() &&
            m20() == n.m20() && m21() == n.m21() && m22() == n.m22() && m23() == n.m23() &&
            m30() == n.m30() && m31() == n.m31() && m32() == n.m32() && m33() == n.m33());
}

void Matrix4x4::set(const float *m)
{
    for(size_t i = 0; i < 16; i++) a_[i] = m[i];
}

const float *Matrix4x4::get() const { return a_.data(); }

// Read-only access functions
float Matrix4x4::m00() const { return a_[0]; }
float Matrix4x4::m01() const { return a_[4]; }
float Matrix4x4::m02() const { return a_[8]; }
float Matrix4x4::m03() const { return a_[12]; }
float Matrix4x4::m10() const { return a_[1]; }
float Matrix4x4::m11() const { return a_[5]; }
float Matrix4x4::m12() const { return a_[9]; }
float Matrix4x4::m13() const { return a_[13]; }
float Matrix4x4::m20() const { return a_[2]; }
float Matrix4x4::m21() const { return a_[6]; }
float Matrix4x4::m22() const { return a_[10]; }
float Matrix4x4::m23() const { return a_[14]; }
float Matrix4x4::m30() const { return a_[3]; }
float Matrix4x4::m31() const { return a_[7]; }
float Matrix4x4::m32() const { return a_[11]; }
float Matrix4x4::m33() const { return a_[15]; }

// Read-write access functions
float &Matrix4x4::m00() { return a_[0]; }
float &Matrix4x4::m01() { return a_[4]; }
float &Matrix4x4::m02() { return a_[8]; }
float &Matrix4x4::m03() { return a_[12]; }
float &Matrix4x4::m10() { return a_[1]; }
float &Matrix4x4::m11() { return a_[5]; }
float &Matrix4x4::m12() { return a_[9]; }
float &Matrix4x4::m13() { return a_[13]; }
float &Matrix4x4::m20() { return a_[2]; }
float &Matrix4x4::m21() { return a_[6]; }
float &Matrix4x4::m22() { return a_[10]; }
float &Matrix4x4::m23() { return a_[14]; }
float &Matrix4x4::m30() { return a_[3]; }
float &Matrix4x4::m31() { return a_[7]; }
float &Matrix4x4::m32() { return a_[11]; }
float &Matrix4x4::m33() { return a_[15]; }

float Matrix4x4::m(uint32_t row, uint32_t col) const
{
    return (row < 4 && col < 4) ? a_[col * 4 + row] : 0.0f;
}

float &Matrix4x4::m(uint32_t row, uint32_t col)
{
    return (row < 4 && col < 4) ? a_[col * 4 + row] : a_[0];
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &n) const
{
    // Unroll the loop, do 1 row at a time.
    Matrix4x4 t;
    float     a0 = m00();
    float     a1 = m01();
    float     a2 = m02();
    float     a3 = m03();
    t.m00() = a0 * n.m00() + a1 * n.m10() + a2 * n.m20() + a3 * n.m30();
    t.m01() = a0 * n.m01() + a1 * n.m11() + a2 * n.m21() + a3 * n.m31();
    t.m02() = a0 * n.m02() + a1 * n.m12() + a2 * n.m22() + a3 * n.m32();
    t.m03() = a0 * n.m03() + a1 * n.m13() + a2 * n.m23() + a3 * n.m33();
    a0 = m10();
    a1 = m11();
    a2 = m12();
    a3 = m13();
    t.m10() = a0 * n.m00() + a1 * n.m10() + a2 * n.m20() + a3 * n.m30();
    t.m11() = a0 * n.m01() + a1 * n.m11() + a2 * n.m21() + a3 * n.m31();
    t.m12() = a0 * n.m02() + a1 * n.m12() + a2 * n.m22() + a3 * n.m32();
    t.m13() = a0 * n.m03() + a1 * n.m13() + a2 * n.m23() + a3 * n.m33();
    a0 = m20();
    a1 = m21();
    a2 = m22();
    a3 = m23();
    t.m20() = a0 * n.m00() + a1 * n.m10() + a2 * n.m20() + a3 * n.m30();
    t.m21() = a0 * n.m01() + a1 * n.m11() + a2 * n.m21() + a3 * n.m31();
    t.m22() = a0 * n.m02() + a1 * n.m12() + a2 * n.m22() + a3 * n.m32();
    t.m23() = a0 * n.m03() + a1 * n.m13() + a2 * n.m23() + a3 * n.m33();
    a0 = m30();
    a1 = m31();
    a2 = m32();
    a3 = m33();
    t.m30() = a0 * n.m00() + a1 * n.m10() + a2 * n.m20() + a3 * n.m30();
    t.m31() = a0 * n.m01() + a1 * n.m11() + a2 * n.m21() + a3 * n.m31();
    t.m32() = a0 * n.m02() + a1 * n.m12() + a2 * n.m22() + a3 * n.m32();
    t.m33() = a0 * n.m03() + a1 * n.m13() + a2 * n.m23() + a3 * n.m33();
    return t;
}

Matrix4x4 &Matrix4x4::operator*=(const Matrix4x4 &n)
{
    *this = *this * n;
    return *this;
}

Matrix4x4 &Matrix4x4::operator*=(float s)
{
    for(size_t r = 0; r < 16; r++) a_[r] *= s;
    return *this;
}

// Transforms a point (applying full homogenous transform, including translation)
HPoint3 Matrix4x4::operator*(const HPoint3 &v) const
{
    return HPoint3(
        a_[0] * v.x + a_[4] * v.y + a_[8] * v.z + a_[12] * v.w,
        a_[1] * v.x + a_[5] * v.y + a_[9] * v.z + a_[13] * v.w,
        a_[2] * v.x + a_[6] * v.y + a_[10] * v.z + a_[14] * v.w,
        a_[3] * v.x + a_[7] * v.y + a_[11] * v.z + a_[15] * v.w
    );
}

HPoint3 Matrix4x4::operator*(const Point3 &v) const
{
    return HPoint3(a_[0] * v.x + a_[4] * v.y + a_[8] * v.z + a_[12],
                   a_[1] * v.x + a_[5] * v.y + a_[9] * v.z + a_[13],
                   a_[2] * v.x + a_[6] * v.y + a_[10] * v.z + a_[14],
                   a_[3] * v.x + a_[7] * v.y + a_[11] * v.z + a_[15]
                );
}

// Transforms a direction vector (applying linear part only, ignoring translation)
Vector3 Matrix4x4::operator*(const Vector3 &v) const
{
    return Vector3(
        a_[0] * v.x + a_[4] * v.y + a_[8] * v.z,
        a_[1] * v.x + a_[5] * v.y + a_[9] * v.z,
        a_[2] * v.x + a_[6] * v.y + a_[10] * v.z
    );
}

// Transforms both the origin (point) and the direction (vector)
Ray3 Matrix4x4::operator*(const Ray3 &ray) const
{
    // Transform origin (w = 1)
    HPoint3 ho = (*this) * ray.o;
    float iw = (ho.w != 0.0f) ? (1.0f / ho.w) : 1.0f; 
    Point3 o(ho.x * iw, ho.y * iw, ho.z * iw);

    // Transform direction as a VECTOR (ignore translation; w = 0)
    Vector3 d = (*this) * ray.d;

    return Ray3(o, d);
}

Matrix4x4 &Matrix4x4::transpose()
{
    *this = get_transpose();
    return *this;
}

Matrix4x4 Matrix4x4::get_transpose() const
{
    Matrix4x4 t;
    t.m00() = m00();
    t.m01() = m10();
    t.m02() = m20();
    t.m03() = m30();
    t.m10() = m01();
    t.m11() = m11();
    t.m12() = m21();
    t.m13() = m31();
    t.m20() = m02();
    t.m21() = m12();
    t.m22() = m22();
    t.m23() = m32();
    t.m30() = m03();
    t.m31() = m13();
    t.m32() = m23();
    t.m33() = m33();
    return t;
}

void Matrix4x4::translate(float x, float y, float z)
{
    m03() += x * m00() + y * m01() + z * m02();
    m13() += x * m10() + y * m11() + z * m12();
    m23() += x * m20() + y * m21() + z * m22();
    m33() += x * m30() + y * m31() + z * m32();
}

void Matrix4x4::scale(float x, float y, float z)
{
    m00() *= x; m10() *= x; m20() *= x; m30() *= x;
    m01() *= y; m11() *= y; m21() *= y; m31() *= y;
    m02() *= z; m12() *= z; m22() *= z; m32() *= z;
}

void Matrix4x4::rotate(float angle, float x, float y, float z)
{
    float len = std::sqrt(x*x + y*y + z*z);
    if (len == 0.0f) return;
    x /= len; y /= len; z /= len;

    const float r = angle * static_cast<float>(M_PI / 180.0);
    const float c = std::cos(r), s = std::sin(r), one_c = 1.0f - c;

    Matrix4x4 R; // identity
    R.m00() = c + one_c * x * x;
    R.m01() = one_c * x * y - s * z;  // <- minus s*z
    R.m02() = one_c * x * z + s * y;  // <- plus  s*y

    R.m10() = one_c * y * x + s * z;  // <- plus  s*z
    R.m11() = c + one_c * y * y;
    R.m12() = one_c * y * z - s * x;  // <- minus s*x

    R.m20() = one_c * z * x - s * y;  // <- minus s*y
    R.m21() = one_c * z * y + s * x;  // <- plus  s*x
    R.m22() = c + one_c * z * z;

    *this *= R; // right-multiply
}


void Matrix4x4::rotate_x(float angle)
{
    const float r = angle * static_cast<float>(M_PI / 180.0);
    const float c = std::cos(r), s = std::sin(r);
    float c01 = m01(), c11 = m11(), c21 = m21(), c31 = m31();
    float c02 = m02(), c12 = m12(), c22 = m22(), c32 = m32();
    m01() =  c * c01 + s * c02;  m11() =  c * c11 + s * c12;  m21() =  c * c21 + s * c22;  m31() =  c * c31 + s * c32;
    m02() = -s * c01 + c * c02;  m12() = -s * c11 + c * c12;  m22() = -s * c21 + c * c22;  m32() = -s * c31 + c * c32;
}

void Matrix4x4::rotate_y(float angle)
{
    const float r = angle * static_cast<float>(M_PI / 180.0);
    const float c = std::cos(r), s = std::sin(r);
    float c00 = m00(), c10 = m10(), c20 = m20(), c30 = m30();
    float c02 = m02(), c12 = m12(), c22 = m22(), c32 = m32();
    m00() =  c * c00 - s * c02;  m10() =  c * c10 - s * c12;  m20() =  c * c20 - s * c22;  m30() =  c * c30 - s * c32;
    m02() =  s * c00 + c * c02;  m12() =  s * c10 + c * c12;  m22() =  s * c20 + c * c22;  m32() =  s * c30 + c * c32;
}

void Matrix4x4::rotate_z(float angle)
{
    const float r = angle * static_cast<float>(M_PI / 180.0);
    const float c = std::cos(r), s = std::sin(r);
    float c00 = m00(), c10 = m10(), c20 = m20(), c30 = m30();
    float c01 = m01(), c11 = m11(), c21 = m21(), c31 = m31();
    m00() =  c * c00 + s * c01;  m10() =  c * c10 + s * c11;  m20() =  c * c20 + s * c21;  m30() =  c * c30 + s * c31;
    m01() = -s * c00 + c * c01;  m11() = -s * c10 + c * c11;  m21() = -s * c20 + c * c21;  m31() = -s * c30 + c * c31;
}


Matrix4x4 Matrix4x4::get_inverse() const
{
    int32_t   j, k;
    int32_t   ind;
    float     v1, v2;
    Matrix4x4 t = *this;
    Matrix4x4 b;
    for(int32_t i = 0; i < 4; i++)
    {
        // Find pivot
        v1 = t.m(i, i);
        ind = i;
        for(j = i + 1; j < 4; j++)
        {
            if(std::abs(t.m(j, i)) > std::abs(v1))
            {
                ind = j;
                v1 = t.m(j, i);
            }
        }

        // Swap columns
        if(ind != i)
        {
            for(j = 0; j < 4; j++)
            {
                v2 = b.m(i, j);
                b.m(i, j) = b.m(ind, j);
                b.m(ind, j) = v2;
                v2 = t.m(i, j);
                t.m(i, j) = t.m(ind, j);
                t.m(ind, j) = v2;
            }
        }

        // The matrix is singular (has no inverse), set the inverse
        // to the identity matrix.
        if(v1 == 0.0f)
        {
            logmsg("InvertMatrix: Singular matrix");
            b.set_identity();
            return b;
        }

        for(j = 0; j < 4; j++)
        {
            t.m(i, j) /= v1;
            b.m(i, j) /= v1;
        }

        // Eliminate column
        for(j = 0; j < 4; j++)
        {
            if(j == i) continue;

            v1 = t.m(j, i);
            for(k = 0; k < 4; k++)
            {
                t.m(j, k) -= t.m(i, k) * v1;
                b.m(j, k) -= b.m(i, k) * v1;
            }
        }
    }
    return b;
}

void Matrix4x4::log(const char *str) const
{
    logmsg("  %s", str);
    logmsg("%.3f %.3f %.3f %.3f", m00(), m01(), m02(), m03());
    logmsg("%.3f %.3f %.3f %.3f", m10(), m11(), m12(), m13());
    logmsg("%.3f %.3f %.3f %.3f", m20(), m21(), m22(), m23());
    logmsg("%.3f %.3f %.3f %.3f", m30(), m31(), m32(), m33());
}

} // namespace cg
