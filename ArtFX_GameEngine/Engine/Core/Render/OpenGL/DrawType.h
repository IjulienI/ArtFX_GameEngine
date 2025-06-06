/**
 * @file DrawType.h
 * @brief Declaration of the DrawType enum, representing different rendering modes.
 */

#pragma once

/**
 * @enum DrawType
 * @brief Enum representing various rendering modes for objects.
 */
enum class DrawType
{
    Lit,        /**< Render objects with lighting effects. */
    Unlit,      /**< Render objects without lighting effects. */
    Wireframe,  /**< Render objects as wireframes. */
    Collision,  /**< Render collision shapes. */
    Debug       /**< Render objects in debug mode. */
};
