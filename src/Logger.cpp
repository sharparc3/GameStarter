#include "Logger.h"

#include <cstdio>
#include <cstdarg>

void LogError(const char* format, ...)
{
    printf(RED "ERROR: ");
    // Initialize the argument list
    va_list args;
    va_start(args, format);

    // Print the formatted error message to stderr
    vfprintf(stderr, format, args);

    // Clean up the argument list
    va_end(args);
    printf("\n" RESET);
}

void LogInfo(const char* format, ...)
{
    printf(BLUE "INFO: ");
    // Initialize the argument list
    va_list args;
    va_start(args, format);

    // Print the formatted error message to stderr
    vfprintf(stdout, format, args);

    // Clean up the argument list
    va_end(args);
    printf("\n" RESET);
}

void LogWarning(const char* format, ...)
{
    printf(YELLOW "WARNING: ");
    // Initialize the argument list
    va_list args;
    va_start(args, format);

    // Print the formatted error message to stderr
    vfprintf(stdout, format, args);

    // Clean up the argument list
    va_end(args);
    printf("\n" RESET);
}

void LogSuccess(const char* format, ...)
{
    printf(GREEN "SUCCESS: ");
    // Initialize the argument list
    va_list args;
    va_start(args, format);

    // Print the formatted error message to stderr
    vfprintf(stdout, format, args);

    // Clean up the argument list
    va_end(args);
    printf("\n" RESET);
}

void Log(const char* format, ...)
{
    // Initialize the argument list
    va_list args;
    va_start(args, format);

    // Print the formatted error message to stderr
    vfprintf(stdout, format, args);

    // Clean up the argument list
    va_end(args);
    printf("\n");
}
