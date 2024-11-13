#pragma once

struct Vec3 {
    float x, y, z;

    Vec3();
    Vec3(float x, float y, float z);

    float Magnitude();

    Vec3& Normalize();

    Vec3& operator = (const Vec3& v);
    bool operator == (const Vec3& v);
    bool operator != (const Vec3& v);

    Vec3 operator + (const Vec3& v) const;
    Vec3 operator - (const Vec3& v) const;
    Vec3 operator * (const float n) const;
    Vec3 operator * (const Vec3& v) const;
    Vec3 operator / (const float n) const;
    Vec3 operator / (const Vec3& v) const;
    Vec3 operator - ();

    Vec3& operator += (const Vec3& v);
    Vec3& operator -= (const Vec3& v);
    Vec3& operator *= (const float n);
    Vec3& operator *= (const Vec3& v);
    Vec3& operator /= (const float n);
    Vec3& operator /= (const Vec3& v);
    
};
