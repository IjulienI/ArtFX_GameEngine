/**
 * @file Maths.h
 * @brief Provides mathematical constants and utility functions for common operations.
 */

#pragma once

#include <limits>
#include <cmath>
#include "Core/Physic/PhysicConstants.h"

/**
 * @namespace Maths
 * @brief Contains mathematical constants and utility functions for calculations.
 */
namespace Maths
{
    /**
     * @brief Value of Pi (π).
     */
    const float PI = 3.1415926535f;

    /**
     * @brief Value of 2π.
     */
    const float TWO_PI = PI * 2.0f;

    /**
     * @brief Value of π/2.
     */
    const float PI_HALVED = PI / 2.0f;

    /**
     * @brief Positive infinity value.
     */
    const float INFINITY_POS = std::numeric_limits<float>::infinity();

    /**
     * @brief Negative infinity value.
     */
    const float INFINITY_NEG = -INFINITY_POS;

    /**
     * @brief Converts degrees to radians.
     * @param degrees Angle in degrees.
     * @return Angle in radians.
     */
    inline float ToRad(float degrees)
    {
        return degrees * PI / 180.0f;
    }

    /**
     * @brief Converts radians to degrees.
     * @param radians Angle in radians.
     * @return Angle in degrees.
     */
    inline float ToDeg(float radians)
    {
        return radians * 180.0f / PI;
    }

    /**
     * @brief Checks if a value is near zero within a given epsilon.
     * @param val Value to check.
     * @param epsilon Tolerance for zero comparison (default is EPSILON).
     * @return True if the value is near zero, false otherwise.
     */
    inline bool NearZero(float val, float epsilon = EPSILON)
    {
        return fabs(val) <= epsilon;
    }

    /**
     * @brief Returns the maximum of two values.
     * @tparam T Type of the values.
     * @param a First value.
     * @param b Second value.
     * @return Maximum value.
     */
    template<typename T>
    T Max(const T& a, const T& b)
    {
        return a < b ? b : a;
    }

    /**
     * @brief Returns the minimum of two values.
     * @tparam T Type of the values.
     * @param a First value.
     * @param b Second value.
     * @return Minimum value.
     */
    template<typename T>
    T Min(const T& a, const T& b)
    {
        return a < b ? a : b;
    }

    /**
     * @brief Clamps a value between a lower and upper bound.
     * @tparam T Type of the value.
     * @param val Value to clamp.
     * @param lower Lower bound.
     * @param upper Upper bound.
     * @return Clamped value.
     */
    template<typename T>
    T Clamp(const T& val, const T& lower, const T& upper)
    {
        return Min(upper, Max(val, lower));
    }

    /**
     * @brief Returns the absolute value of a number.
     * @param val Value to compute the absolute value of.
     * @return Absolute value.
     */
    inline float Abs(float val)
    {
        return fabs(val);
    }

    /**
     * @brief Computes the cosine of an angle.
     * @param angle Angle in radians.
     * @return Cosine of the angle.
     */
    inline float Cos(float angle)
    {
        return cosf(angle);
    }

    /**
     * @brief Computes the sine of an angle.
     * @param angle Angle in radians.
     * @return Sine of the angle.
     */
    inline float Sin(float angle)
    {
        return sinf(angle);
    }

    /**
     * @brief Computes the tangent of an angle.
     * @param angle Angle in radians.
     * @return Tangent of the angle.
     */
    inline float Tan(float angle)
    {
        return tanf(angle);
    }

    /**
     * @brief Computes the arccosine of a value.
     * @param angle Value to compute the arccosine of.
     * @return Arccosine of the value.
     */
    inline float ACos(float angle)
    {
        return acosf(angle);
    }

    /**
     * @brief Computes the arctangent of two values.
     * @param opposite Opposite side length.
     * @param adjacent Adjacent side length.
     * @return Arctangent of the values.
     */
    inline float ATan2(float opposite, float adjacent)
    {
        return atan2f(opposite, adjacent);
    }

    /**
     * @brief Computes the cotangent of an angle.
     * @param angle Angle in radians.
     * @return Cotangent of the angle.
     */
    inline float Cot(float angle)
    {
        return 1.0f / Tan(angle);
    }

    /**
     * @brief Performs linear interpolation between two values.
     * @param a Start value.
     * @param b End value.
     * @param t Interpolation factor (0.0 to 1.0).
     * @return Interpolated value.
     */
    inline float Lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

    /**
     * @brief Computes the square root of a value.
     * @param val Value to compute the square root of.
     * @return Square root of the value.
     */
    inline float Sqrt(float val)
    {
        return sqrtf(val);
    }

    /**
     * @brief Computes the remainder of a division operation.
     * @param numer Numerator.
     * @param denom Denominator.
     * @return Remainder of the division.
     */
    inline float Fmod(float numer, float denom)
    {
        return std::fmod(numer, denom);
    }

    /**
     * @brief Rounds a floating-point value to the nearest integer.
     * @param val Value to round.
     * @return Rounded integer value.
     */
    inline int Round(float val)
    {
        return static_cast<int>(val);
    }
}
