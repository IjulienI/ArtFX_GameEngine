#include "Vec4.h"
#include "Maths.h"

float Vec4::LengthSqr() const
{
    return (x * x + y * y + z * z + w * w);
}

float Vec4::Length() const
{
    return (Maths::Sqrt(LengthSqr()));
}

void Vec4::Normalize()
{
    float len = Length();
    x /= len;
    y /= len;
    z /= len;
    w /= len;
}
