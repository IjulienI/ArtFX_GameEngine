#pragma once

class Vec4
{
    friend class Matrix4;

public:
	float x;
	float y;
	float z;
	float w;

	Vec4()
		:x(0.0f)
		,y(0.0f)
		,z(0.0f)
		,w(0.0f)
	{}

	explicit Vec4(float inX, float inY, float inZ, float inW)
		:x(inX)
		,y(inY)
		,z(inZ)
		,w(inW)
	{}

	float LengthSqr() const;
	float Length() const;
	void Normalize();

	// Cast to a const float pointer
	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	// Set all four components in one line
	void Set(float inX, float inY, float inZ, float inW)
	{
		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}

	float& operator[](int i)
	{
		return *(reinterpret_cast<float*>(&x) + i);
	}

		// Vector addition (a + b)
	friend Vec4 operator+(const Vec4& a, const Vec4& b)
	{
		return Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	// Vector subtraction (a - b)
	friend Vec4 operator-(const Vec4& a, const Vec4& b)
	{
		return Vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	// Component-wise multiplication
	friend Vec4 operator*(const Vec4& left, const Vec4& right)
	{
		return Vec4(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
	}

	// Scalar multiplication
	friend Vec4 operator*(const Vec4& vec, float scalar)
	{
		return Vec4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
	}

	// Scalar multiplication
	friend Vec4 operator*(float scalar, const Vec4& vec)
	{
		return Vec4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
	}

	// Scalar *=
	Vec4& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	// Vector +=
	Vec4& operator+=(const Vec4& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		w += right.w;
		return *this;
	}

	// Vector -=
	Vec4& operator-=(const Vec4& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		w -= right.w;
		return *this;
	}

	// Normalize the provided vector
	static Vec4 Normalize(const Vec4& vec)
	{
		Vec4 temp = vec;
		temp.Normalize();
		return temp;
	}

	// Dot product between two vectors (a dot b)
	static float Dot(const Vec4& a, const Vec4& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	// Cross product between two vectors (a cross b)
	static Vec4 Cross(const Vec4& a, const Vec4& b)
	{
		Vec4 temp;
		temp.x = a.y * b.z - a.z * b.y;
		temp.y = a.z * b.x - a.x * b.z;
		temp.z = a.x * b.y - a.y * b.x;
		return temp;
	}

	// Lerp from A to B by f
	static Vec4 Lerp(const Vec4& a, const Vec4& b, float f)
	{
		return Vec4(a + f * (b - a));
	}

	// Reflect V about (normalized) N
	static Vec4 Reflect(const Vec4& v, const Vec4& n)
	{
		return v - 2.0f * Vec4::Dot(v, n) * n;
	}

};
