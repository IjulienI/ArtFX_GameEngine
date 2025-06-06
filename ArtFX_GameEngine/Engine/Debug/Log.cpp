/**
 * @file Log.cpp
 * @brief Implementation of the Log class, which provides logging functionality using SDL.
 */

#include "Log.h"
#include <SDL_error.h>

/**
 * @brief Logs an informational message.
 * @param message The message to log.
 */
void Log::Info(const std::string& message)
{
	SDL_Log(message.c_str());
}

/**
 * @brief Logs an error message with a specific category.
 * @param category The category of the log message.
 * @param message The error message to log.
 */
void Log::Error(LogType category, const std::string& message)
{
	SDL_LogError(static_cast<int>(category), "%s | SDL : %s", message.c_str(), SDL_GetError());
}

/**
 * @brief Logs a warning message with a specific category.
 * @param category The category of the log message.
 * @param message The warning message to log.
 */
void Log::Warning(LogType category, const std::string& message)
{
	SDL_LogWarn(static_cast<int>(category), "%s | SDL : %s", message.c_str(), SDL_GetError());
}
