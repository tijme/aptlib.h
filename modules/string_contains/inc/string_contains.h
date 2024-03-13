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
 * Check if the given needle is present in the given haystack (case sensitive).
 * 
 * @param char* haystack The haystack to search in.
 * @param char* needle The needle to search for.
 * @param bool Positive if the needle was found in the haystack.
 */
bool stringContainsCS(char* haystack, char* needle);

/**
 * Check if the given needle is present in the given haystack (case insensitive).
 * 
 * @param char* haystack The haystack to search in.
 * @param char* needle The needle to search for.
 * @param bool Positive if the needle was found in the haystack.
 */
bool stringContainsCI(char* haystack, char* needle);

/**
 * Check if the given needle is present in the given haystack.
 * 
 * @param char* haystack The haystack to search in.
 * @param char* needle The needle to search for.
 * @param bool caseSensitive If a case sensitive check should be performed.
 * @param bool Positive if the needle was found in the haystack.
 */
bool stringContains(char* haystack, char* needle, bool caseSensitive);