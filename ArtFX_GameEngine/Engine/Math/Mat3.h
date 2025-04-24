#pragma once
#include "Quaternion.h"

class Mat3
{
public:
    float m[3][3];

    Mat3();

    static Mat3 Identity()
    {
        return Mat3();
    }

    static Mat3 CreateFromQuaternion(const Quaternion& q);

    Mat3 Transpose() const;

    Mat3 Inverse() const;

    float Determinant() const;

    Mat3 operator*(const Mat3& rhs) const;

    Vec3 operator*(const Vec3& v) const;

    static Mat3 CrossProductMatrix(const Vec3& v);
};
