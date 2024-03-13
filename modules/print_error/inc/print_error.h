/**
 * Only include this header file once.
 */
#pragma once

/**
 * Disable the Spectre warning (MSVC C5045). Otherwise we cannot access arrays with unsafe indexes.
 */
#pragma warning(disable :5045)

/**
 * Standard Input Output.
 * 
 * Defines three variable types, several macros, and various functions for performing input and output.
 * https://www.tutorialspoint.com/c_standard_library/stdio_h.htm
 */
#include <stdio.h>

/**
 * Windows API.
 * 
 * Contains declarations for all of the functions, macro's & data types in the Windows API.
 * Define 'WIN32_LEAN_AND_MEAN' to make sure windows.h compiles without warnings.
 * https://docs.microsoft.com/en-us/previous-versions//aa383749(v=vs.85)?redirectedfrom=MSDN
 */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/**
 * Retrieve a human-readable string describing the given error code.
 * 
 * @param DWORD errorCode The error code to convert.
 * @returns char* The human-readable string.
 */
char* GetMessageFromError(DWORD errorCode);

/**
 * Print last error to the console
 * 
 * @returns char* The human-readable string.
 */
char* GetMessageFromLastError();

/**
 * Print a human-readable string, describing the given error code, to the console.
 * 
 * @param DWORD errorCode The error code to print a message for.
 */
void PrintMessageFromError(DWORD errorCode);

/**
 * Print a human-readable string, describing the last error code, to the console.
 */
void PrintMessageFromLastError();
