#include "geometry/matrix.hpp"

#include "geometry/geometry.hpp"

#include <cmath>

namespace cg
{

Matrix4x4::Matrix4x4() { set_identity(); }

void Matrix4x4::set_identity()
{
    // Defined later
}

Matrix4x4::Matrix4x4(const Matrix4x4 &n)
{
    // Defined later
}

Matrix4x4 &Matrix4x4::operator=(const Matrix4x4 &n)
{
    // Defined later
    return *this;
}

bool Matrix4x4::operator==(const Matrix4x4 &n) const
{
    // Defined later
    return false;
}

void Matrix4x4::set(const float *m)
{
    // Defined later
}

const float *Matrix4x4::get() const { return a_.data(); }

// Read-only access functions
float Matrix4x4::m00() const { return a_[0]; } // Defined later
float Matrix4x4::m01() const { return a_[0]; } // Defined later
float Matrix4x4::m02() const { return a_[0]; } // Defined later
float Matrix4x4::m03() const { return a_[0]; } // Defined later
float Matrix4x4::m10() const { return a_[0]; } // Defined later
float Matrix4x4::m11() const { return a_[0]; } // Defined later
float Matrix4x4::m12() const { return a_[0]; } // Defined later
float Matrix4x4::m13() const { return a_[0]; } // Defined later
float Matrix4x4::m20() const { return a_[0]; } // Defined later
float Matrix4x4::m21() const { return a_[0]; } // Defined later
float Matrix4x4::m22() const { return a_[0]; } // Defined later
float Matrix4x4::m23() const { return a_[0]; } // Defined later
float Matrix4x4::m30() const { return a_[0]; } // Defined later
float Matrix4x4::m31() const { return a_[0]; } // Defined later
float Matrix4x4::m32() const { return a_[0]; } // Defined later
float Matrix4x4::m33() const { return a_[0]; } // Defined later

// Read-write access functions
float &Matrix4x4::m00() { return a_[0]; } // Defined later
float &Matrix4x4::m01() { return a_[0]; } // Defined later
float &Matrix4x4::m02() { return a_[0]; } // Defined later
float &Matrix4x4::m03() { return a_[0]; } // Defined later
float &Matrix4x4::m10() { return a_[0]; } // Defined later
float &Matrix4x4::m11() { return a_[0]; } // Defined later
float &Matrix4x4::m12() { return a_[0]; } // Defined later
float &Matrix4x4::m13() { return a_[0]; } // Defined later
float &Matrix4x4::m20() { return a_[0]; } // Defined later
float &Matrix4x4::m21() { return a_[0]; } // Defined later
float &Matrix4x4::m22() { return a_[0]; } // Defined later
float &Matrix4x4::m23() { return a_[0]; } // Defined later
float &Matrix4x4::m30() { return a_[0]; } // Defined later
float &Matrix4x4::m31() { return a_[0]; } // Defined later
float &Matrix4x4::m32() { return a_[0]; } // Defined later
float &Matrix4x4::m33() { return a_[0]; } // Defined later

float Matrix4x4::m(uint32_t row, uint32_t col) const
{
    // Defined later
    return 0.0f;
}

float &Matrix4x4::m(uint32_t row, uint32_t col)
{
    // Defined later
    return a_[0];
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &n) const
{
    // Defined later
    Matrix4x4 t;
    return t;
}

Matrix4x4 &Matrix4x4::operator*=(const Matrix4x4 &n)
{
    *this = *this * n;
    return *this;
}

Matrix4x4 &Matrix4x4::operator*=(float s)
{
    // Defined later
    return *this;
}

HPoint3 Matrix4x4::operator*(const HPoint3 &v) const
{
    // Student to define - Module 4
    return HPoint3(0.0f, 0.0f, 0.0f, 1.0f);
}

HPoint3 Matrix4x4::operator*(const Point3 &v) const
{
    // Student to define - Module 3
    return HPoint3(0.0f, 0.0f, 0.0f, 1.0f);
}

Vector3 Matrix4x4::operator*(const Vector3 &v) const
{
    // Student to define - Module 4
    return Vector3(0.0f, 0.0f, 0.0f);
}

Ray3 Matrix4x4::operator*(const Ray3 &ray) const
{
    // Student to define - Module 4
    return Ray3();
}

Matrix4x4 &Matrix4x4::transpose()
{
    // Defined later
    return *this;
}

Matrix4x4 Matrix4x4::get_transpose() const
{
    // Defined later
    Matrix4x4 t;
    return t;
}

void Matrix4x4::translate(float x, float y, float z)
{
    // Student to define - Module 4
}

void Matrix4x4::scale(float x, float y, float z)
{
    // Student to define - Module 4
}

void Matrix4x4::rotate(float angle, float x, float y, float z)
{
    // Student to define - Module 4
}

void Matrix4x4::rotate_x(float angle)
{
    // Student to define - Module 4
}

void Matrix4x4::rotate_y(float angle)
{
    // Student to define - Module 4
}

void Matrix4x4::rotate_z(float angle)
{
    // Student to define - Module 4
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
            extern void logmsg(const char *message, ...);
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
    extern void logmsg(const char *message, ...);
    logmsg("  %s", str);
    logmsg("%.3f %.3f %.3f %.3f", m00(), m01(), m02(), m03());
    logmsg("%.3f %.3f %.3f %.3f", m10(), m11(), m12(), m13());
    logmsg("%.3f %.3f %.3f %.3f", m20(), m21(), m22(), m23());
    logmsg("%.3f %.3f %.3f %.3f", m30(), m31(), m32(), m33());
}

} // namespace cg
