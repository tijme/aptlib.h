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
 * Booleans.
 * 
 * Defines boolean types.
 * https://pubs.opengroup.org/onlinepubs/007904975/basedefs/stdbool.h.html
 */
#include <stdbool.h>

/**
 * Print given value in HEX
 * 
 * @param char* value An array of chars to print in HEX.
 * @param size_t length The amount of bytes/chars to print.
 * @param bool reverse Reverse the output (e.g. for a pointer).
 */
void printInHex(char* lpBuffer, size_t lpNumberOfBytesRead, bool reverse);
