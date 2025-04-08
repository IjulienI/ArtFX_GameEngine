#pragma once

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

	// Component-wise multiplication
	friend Vec3 operator*(const Vec3& left, const Vec3& right)
	{
		return Vec3(left.x * right.x, left.y * right.y, left.z * right.z);
	}

	// Scalar multiplication
	friend Vec3 operator*(const Vec3& vec, float scalar)
	{
		return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	// Scalar multiplication
	friend Vec3 operator*(float scalar, const Vec3& vec)
	{
		return Vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	// Scalar *=
	Vec3& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	// Vector +=
	Vec3& operator+=(const Vec3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	// Vector -=
	Vec3& operator-=(const Vec3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
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

	// Lerp from A to B by f
	static Vec3 Lerp(const Vec3& a, const Vec3& b, float f)
	{
		return Vec3(a + f * (b - a));
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

