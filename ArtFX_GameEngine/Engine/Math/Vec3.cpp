#include "Vec3.h"
#include "Matrix4.h"
#include "Quaternion.h"

const Vec3 Vec3::zero(0.0f, 0.0f, 0.f);
const Vec3 Vec3::one(1.0f, 1.0f, 1.0f);
const Vec3 Vec3::unitX(1.0f, 0.0f, 0.0f);
const Vec3 Vec3::unitY(0.0f, 1.0f, 0.0f);
const Vec3 Vec3::unitZ(0.0f, 0.0f, 1.0f);
const Vec3 Vec3::negUnitX(-1.0f, 0.0f, 0.0f);
const Vec3 Vec3::negUnitY(0.0f, -1.0f, 0.0f);
const Vec3 Vec3::negUnitZ(0.0f, 0.0f, -1.0f);
const Vec3 Vec3::infinity(Maths::INFINITY_POS, Maths::INFINITY_POS, Maths::INFINITY_POS);
const Vec3 Vec3::negInfinity(Maths::INFINITY_NEG, Maths::INFINITY_NEG, Maths::INFINITY_NEG);

void Vec3::Set(float xP, float yP, float zP)
{
	x = xP;
	y = yP;
	z = zP;
}

float Vec3::LengthSq() const
{
	return (x * x + y * y + z * z);
}

float Vec3::Length() const
{
	return (Maths::Sqrt(LengthSq()));
}

void Vec3::Normalize()
{
	float len = Length();
	x /= len;
	y /= len;
	z /= len;
}

float Vec3::Distance(Vec3 v)
{
	float difX = x - v.x;
	float difY = y - v.y;
	float difZ = z - v.z;
	return static_cast<float>(Maths::Sqrt((difX * difX) + (difY * difY) + (difZ * difZ)));
}


Vec3 Vec3::Transform(Vec3& vec, Matrix4& mat, float w)
{
	Vec3 retVal;
	retVal.x = vec.x * mat(0,0) + vec.y * mat(1,0) +
		vec.z * mat(2,0) + w * mat(3,0);
	retVal.y = vec.x * mat(0,1) + vec.y * mat(1,1) +
		vec.z * mat(2,1) + w * mat(3,1);
	retVal.z = vec.x * mat(0,2) + vec.y * mat(1,2) +
		vec.z * mat(2,2) + w * mat(3,2);
	//ignore w since we aren't returning a new value for it...
	return retVal;
}

Vec3 Vec3::TransformWithPerspDiv(Vec3& vec, Matrix4& mat, float w)
{
	Vec3 retVal;
	retVal.x = vec.x * mat(0,0) + vec.y * mat(1,0) +
		vec.z * mat(2,0) + w * mat(3,0);
	retVal.y = vec.x * mat(0,1) + vec.y * mat(1,1) +
		vec.z * mat(2,1) + w * mat(3,1);
	retVal.z = vec.x * mat(0,2) + vec.y * mat(1,2) +
		vec.z * mat(2,2) + w * mat(3,2);
	float transformedW = vec.x * mat(0,3) + vec.y * mat(1,3) +
		vec.z * mat(2,3) + w * mat(3,3);
	if (!Maths::NearZero(Maths::Abs(transformedW)))
	{
		transformedW = 1.0f / transformedW;
		retVal *= transformedW;
	}
	return retVal;
}


Vec3 Vec3::Transform(const Vec3& v, const Quaternion& q)
{
	// v + 2.0*cross(q.xyz, cross(q.xyz,v) + q.w*v);
	Vec3 qv(q.x, q.y, q.z);
	Vec3 retVal = v;
	retVal += 2.0f * Vec3::Cross(qv, Vec3::Cross(qv, v) + q.w * v);
	return retVal;
}
