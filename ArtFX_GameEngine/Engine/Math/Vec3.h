#pragma once
#include <sstream>
#include <string>

#include "Core/Physic/PhysicConstants.h"

class Vec3
{

public:
	float x;
	float y;
	float z;

	Vec3(): x(0.0f), y(0.0f), z(0.0f) {}

	explicit Vec3(float xP, float yP, float zP)
		:x(xP), y(yP), z(zP) {}

	void Set(float xP, float yP, float zP);
	float LengthSq() const;
	float Length() const;
	void Normalize();
	float Distance(Vec3& v) const;
	Vec3 UnitVector() const;
	bool NearZero(float epsilon = EPSILON) const;

	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	// Vector addition (a + b)
	friend Vec3 operator+(const Vec3& a, const Vec3& b)
	{
		return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	// Vector subtraction (a - b)
	friend Vec3 operator-(const Vec3& a, const Vec3& b)
	{
		return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	Vec3 operator-() const
	{
		return Vec3(-x,-y,-z);
	}

	float operator |(const Vec3& v) const
	{
		return Vec3::Dot(*this, v);
	}

	// Component-wise multiplication
	Vec3 operator*(const Vec3& v) const
	{
		return Vec3(x * v.x, y * v.y, z * v.z);
	}

	// Scalar multiplication
	Vec3 operator*(float scalar) const
	{
		return Vec3(x * scalar, y * scalar, z * scalar);
	}

	friend Vec3 operator*(float scalar, const Vec3& v)
	{
		return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
	}

	std::string ToString() const
	{
		std::ostringstream os;
		os<<"x: "<<x<<" y: "<<y<<" z: "<<z;
		return os.str();
	}

	friend std::ostream& operator<<(std::ostream& o,const Vec3& v)
	{
		return o<<v.ToString();
	}
	

	// Scalar
	Vec3& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	// Vector	
	Vec3& operator+=(const Vec3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}
	
	Vec3& operator-=(const Vec3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	Vec3& operator*=(const Vec3& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	Vec3& operator/=(float scalar)
	{
		if (scalar != 0.0f) {
			x /= scalar;
			y /= scalar;
			z /= scalar;
		}
		return *this;
	}

	bool operator<(const Vec3& right) const
	{
		return (x < right.x && y < right.y && z < right.z);
	}

	bool operator>(const Vec3& right) const
	{
		return (x > right.x && y > right.y && z > right.z);
	}

	static Vec3 Min(const Vec3& a, const Vec3& b)
	{
		return a < b ? b : a;
	}

	static Vec3 Max(const Vec3& a, const Vec3& b)
	{
		return a > b ? b: a;
	}

	// Normalize the provided vector
	static Vec3 Normalize(const Vec3& vec)
	{
		Vec3 temp = vec;
		temp.Normalize();
		return temp;
	}

	// Dot product between two vectors (a dot b)
	static float Dot(const Vec3& a, const Vec3& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	// Cross product between two vectors (a cross b)
	static Vec3 Cross(const Vec3& a, const Vec3& b)
	{
		Vec3 temp;
		temp.x = a.y * b.z - a.z * b.y;
		temp.y = a.z * b.x - a.x * b.z;
		temp.z = a.x * b.y - a.y * b.x;
		return temp;
	}

	Vec3 operator ^(const Vec3& v) const
	{
		return Vec3::Cross(*this, v);
	}

	// Lerp from A to B by f
	static Vec3 Lerp(const Vec3& a, const Vec3& b, float f)
	{
		return a + (b - a) * f;
	}

	// Reflect V about (normalized) N
	static Vec3 Reflect(const Vec3& v, const Vec3& n)
	{
		return v - 2.0f * Vec3::Dot(v, n) * n;
	}

	static Vec3 Transform(Vec3& vec, class Matrix4& mat, float w = 1.0f);

	// This will transform the vector and renormalize the w component
	static Vec3 TransformWithPerspDiv(Vec3& vec, class Matrix4& mat, float w = 1.0f);

	// Transform a Vector3 by a quaternion
	static Vec3 Transform(const Vec3& v, const class Quaternion& q);

	static const Vec3 zero;
	static const Vec3 one;
	static const Vec3 unitX;
	static const Vec3 unitY;
	static const Vec3 unitZ;
	static const Vec3 negUnitX;
	static const Vec3 negUnitY;
	static const Vec3 negUnitZ;
	static const Vec3 infinity;
	static const Vec3 negInfinity;
};

