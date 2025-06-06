/**
 * @file PhysicConstants.h
 * @brief Contains physics-related constants such as gravity, epsilon, and simulation step size.
 */

#pragma once 

/**
 * @brief Gravity acceleration constant (in meters per second squared).
 */
const float GRAVITY = -9.81f;

/**
 * @brief Small epsilon value for floating point comparisons.
 */
const float EPSILON = 1e-6f;

/**
 * @brief Physics simulation step size (in seconds).
 */
const float DELTA_STEP = 1.0f / 240.0f;

/**
 * @brief Number of pixels per meter for physics to rendering conversion.
 */
const unsigned int PIXELS_PER_METER = 10;
