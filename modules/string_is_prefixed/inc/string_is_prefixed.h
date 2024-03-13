/**
 * Only include this header file once.
 */
#pragma once

/**
 * Disable the Spectre warning (MSVC C5045). Otherwise we cannot access arrays with unsafe indexes.
 */
#pragma warning(disable :5045)

/**
 * Booleans.
 * 
 * Defines boolean types.
 * https://pubs.opengroup.org/onlinepubs/007904975/basedefs/stdbool.h.html
 */
#include <stdbool.h>

/**
 * Check if the given prefix is indeed a prefix in the given string (case sensitive).
 * 
 * @param char* string The string to check the prefix for.
 * @param char* possiblePrefix The prefix to search for.
 * @param bool caseSensitive If a case sensitive check should be performed.
 * @param bool Positive if the string is prefixed with the possible prefix.
 */
bool stringIsPrefixedCS(char* string, char* possiblePrefix);

/**
 * Check if the given prefix is indeed a prefix in the given string (case insensitive).
 * 
 * @param char* string The string to check the prefix for.
 * @param char* possiblePrefix The prefix to search for.
 * @param bool caseSensitive If a case sensitive check should be performed.
 * @param bool Positive if the string is prefixed with the possible prefix.
 */
bool stringIsPrefixedCI(char* string, char* possiblePrefix);

/**
 * Check if the given prefix is indeed a prefix in the given string.
 * 
 * @param char* string The string to check the prefix for.
 * @param char* possiblePrefix The prefix to search for.
 * @param bool caseSensitive If a case sensitive check should be performed.
 * @param bool Positive if the string is prefixed with the possible prefix.
 */
bool stringIsPrefixed(char* string, char* possiblePrefix, bool caseSensitive);