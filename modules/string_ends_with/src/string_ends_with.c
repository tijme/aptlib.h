/**
 * The MIT License (MIT)
 * =====================
 * 
 * Copyright (c) 2024 Tijme Gommers. All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the “Software”), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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
 * Local includes
 */
#include "../inc/string_ends_with.h"

/**
 * Check if the given affix indeed ends with in the given string (case sensitive).
 * 
 * @param char* string The string to check the affix for.
 * @param char* possibleAffix The affix to search for.
 * @param bool caseSensitive If a case sensitive check should be performed.
 * @param bool Positive if the string is affixed with the possible affix.
 */
bool stringEndsWithCS(char* string, char* possibleAffix) {
    size_t stringLength = strlen(string);
    size_t affixLength = strlen(possibleAffix);

    if (affixLength >  stringLength)
        return 0;

    return strncmp(string + stringLength - affixLength, possibleAffix, affixLength) == 0;
}

/**
 * Check if the given affix is indeed a affix in the given string (case insensitive).
 * 
 * @param char* string The string to check the affix for.
 * @param char* possibleAffix The affix to search for.
 * @param bool caseSensitive If a case sensitive check should be performed.
 * @param bool Positive if the string is affixed with the possible affix.
 */
bool stringEndsWithCI(char* string, char* possibleAffix) {
    size_t stringLength = strlen(string);
    size_t affixLength = strlen(possibleAffix);

    if (affixLength >  stringLength)
        return 0;

    return strncasecmp(string + stringLength - affixLength, possibleAffix, affixLength) == 0;
}

/**
 * Check if the given affix is indeed a affix in the given string.
 * 
 * @param char* string The string to check the affix for.
 * @param char* possibleAffix The affix to search for.
 * @param bool caseSensitive If a case sensitive check should be performed.
 * @param bool Positive if the string is affixed with the possible affix.
 */
bool stringEndsWith(char* string, char* possibleAffix, bool caseSensitive) {
    return caseSensitive ? stringEndsWithCS(string, possibleAffix) : stringEndsWithCI(string, possibleAffix);
}