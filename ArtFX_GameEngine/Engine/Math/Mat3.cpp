#include "Mat3.h"

Mat3::Mat3()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

Mat3 Mat3::CreateFromQuaternion(const Quaternion& q)
{
    Mat3 result;
    float x = q.x, y = q.y, z = q.z, w = q.w;

    result.m[0][0] = 1 - 2 * y * y - 2 * z * z;
    result.m[0][1] = 2 * x * y - 2 * z * w;
    result.m[0][2] = 2 * x * z + 2 * y * w;

    result.m[1][0] = 2 * x * y + 2 * z * w;
    result.m[1][1] = 1 - 2 * x * x - 2 * z * z;
    result.m[1][2] = 2 * y * z - 2 * x * w;

    result.m[2][0] = 2 * x * z - 2 * y * w;
    result.m[2][1] = 2 * y * z + 2 * x * w;
    result.m[2][2] = 1 - 2 * x * x - 2 * y * y;

    return result;
}

Mat3 Mat3::Transpose() const
{
    Mat3 result;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            result.m[i][j] = m[j][i];
        }
    }
    return result;
}

Mat3 Mat3::Inverse() const
{
    Mat3 result;
    float det = Determinant();
    if (std::abs(det) < EPSILON) return Identity();

    result.m[0][0] =  (m[1][1] * m[2][2] - m[1][2] * m[2][1]) / det;
    result.m[0][1] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]) / det;
    result.m[0][2] =  (m[0][1] * m[1][2] - m[0][2] * m[1][1]) / det;

    result.m[1][0] = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]) / det;
    result.m[1][1] =  (m[0][0] * m[2][2] - m[0][2] * m[2][0]) / det;
    result.m[1][2] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]) / det;

    result.m[2][0] =  (m[1][0] * m[2][1] - m[1][1] * m[2][0]) / det;
    result.m[2][1] = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]) / det;
    result.m[2][2] =  (m[0][0] * m[1][1] - m[0][1] * m[1][0]) / det;

    return result;
}

float Mat3::Determinant() const
{
    return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
       m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
       m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

Mat3 Mat3::operator*(const Mat3& rhs) const
{
    Mat3 result;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            result.m[i][j] = 0.0f;
            for (int k = 0; k < 3; ++k)
                result.m[i][j] += m[i][k] * rhs.m[k][j];
        }
    return result;
}

Vec3 Mat3::operator*(const Vec3& v) const
{
    return Vec3(
    m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z,
    m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z,
    m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z
);
}

Mat3 Mat3::CrossProductMatrix(const Vec3& v)
{
    Mat3 result;
    result.m[0][0] = 0.0f; result.m[0][1] = -v.z; result.m[0][2] = v.y;
    result.m[1][0] = v.z;  result.m[1][1] = 0.0f; result.m[1][2] = -v.x;
    result.m[2][0] = -v.y; result.m[2][1] = v.x;  result.m[2][2] = 0.0f;
    return result;
}
