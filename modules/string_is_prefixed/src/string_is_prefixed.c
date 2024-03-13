/**
 * Booleans.
 * 
 * Defines boolean types.
 * https://pubs.opengroup.org/onlinepubs/007904975/basedefs/stdbool.h.html
 */
#include <stdbool.h>

/**
 * Strings.
 * 
 * Defines one variable type, one macro, and various functions for manipulating arrays of characters.
 * https://www.tutorialspoint.com/c_standard_library/string_h.htm
 */
#include <string.h>

/**
 * Check if the given prefix is indeed a prefix in the given string (case sensitive).
 * 
 * @param char* string The string to check the prefix for.
 * @param char* possiblePrefix The prefix to search for.
 * @param bool caseSensitive If a case sensitive check should be performed.
 * @param bool Positive if the string is prefixed with the possible prefix.
 */
bool stringIsPrefixedCS(char* string, char* possiblePrefix) {
    return strncmp(possiblePrefix, string, strlen(possiblePrefix)) == 0;
}

/**
 * Check if the given prefix is indeed a prefix in the given string (case insensitive).
 * 
 * @param char* string The string to check the prefix for.
 * @param char* possiblePrefix The prefix to search for.
 * @param bool caseSensitive If a case sensitive check should be performed.
 * @param bool Positive if the string is prefixed with the possible prefix.
 */
bool stringIsPrefixedCI(char* string, char* possiblePrefix) {
    return strncasecmp(possiblePrefix, string, strlen(possiblePrefix)) == 0;
}

/**
 * Check if the given prefix is indeed a prefix in the given string.
 * 
 * @param char* string The string to check the prefix for.
 * @param char* possiblePrefix The prefix to search for.
 * @param bool caseSensitive If a case sensitive check should be performed.
 * @param bool Positive if the string is prefixed with the possible prefix.
 */
bool stringIsPrefixed(char* string, char* possiblePrefix, bool caseSensitive) {
    return caseSensitive ? stringIsPrefixedCS(string, possiblePrefix) : stringIsPrefixedCI(string, possiblePrefix);
}