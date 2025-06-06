/**
 * @file Log.h
 * @brief Declaration of the Log class, which provides logging functionality using SDL.
 */

#pragma once
#include "SDL_log.h"
#include <iostream>

/**
 * @enum LogType
 * @brief Enum representing different categories of log messages.
 */
enum class LogType
{
	Application = SDL_LOG_CATEGORY_APPLICATION, /**< Application-related logs. */
	Assert = SDL_LOG_CATEGORY_ASSERT,           /**< Assertion-related logs. */
	Audio = SDL_LOG_CATEGORY_AUDIO,             /**< Audio-related logs. */
	Error = SDL_LOG_CATEGORY_ERROR,             /**< Error-related logs. */
	Input = SDL_LOG_CATEGORY_INPUT,             /**< Input-related logs. */
	Render = SDL_LOG_CATEGORY_RENDER,           /**< Render-related logs. */
	System = SDL_LOG_CATEGORY_SYSTEM,           /**< System-related logs. */
	Test = SDL_LOG_CATEGORY_TEST,               /**< Test-related logs. */
	Video = SDL_LOG_CATEGORY_VIDEO              /**< Video-related logs. */
};

/**
 * @class Log
 * @brief Provides static methods for logging messages with different severity levels and categories.
 */
class Log
{
public:
	Log() = delete; /**< Deleted default constructor to prevent instantiation. */
	Log(const Log&) = delete; /**< Deleted copy constructor. */
	Log& operator=(const Log&) = delete; /**< Deleted assignment operator. */

	/**
	 * @brief Logs an informational message.
	 * @param message The message to log.
	 */
	static void Info(const std::string& message);

	/**
	 * @brief Logs an error message with a specific category.
	 * @param category The category of the log message.
	 * @param message The error message to log.
	 */
	static void Error(LogType category, const std::string& message);

	/**
	 * @brief Logs a warning message with a specific category.
	 * @param category The category of the log message.
	 * @param message The warning message to log.
	 */
	static void Warning(LogType category, const std::string& message);
};
