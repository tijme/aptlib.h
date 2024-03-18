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
 * Characters.
 * 
 * Defines several functions that are useful for testing and mapping characters.
 * https://www.tutorialspoint.com/c_standard_library/ctype_h.htm
 */
#include <ctype.h>

/**
 * Local includes
 */
#include "../inc/string_contains.h"

/**
 * Check if the given needle is present in the given haystack (case sensitive).
 * 
 * @param char* haystack The haystack to search in.
 * @param char* needle The needle to search for.
 * @param bool Positive if the needle was found in the haystack.
 */
bool stringContainsCS(char* haystack, char* needle) {
    return strstr(haystack, needle) != NULL;
}

/**
 * Check if the given needle is present in the given haystack (case insensitive).
 * 
 * @param char* haystack The haystack to search in.
 * @param char* needle The needle to search for.
 * @param bool Positive if the needle was found in the haystack.
 */
bool stringContainsCI(char* haystack, char* needle) {
    const char* p1 = haystack;
    const char* p2 = needle;
    const char* r = *p2 == 0 ? haystack : 0;

    while( *p1 != 0 && *p2 != 0 ) {
        if( tolower((unsigned char)*p1) == tolower((unsigned char)*p2)) {
            if(r == 0) {
                r = p1;
            }

            p2++;
        } else {
            p2 = needle;
            if(r != 0) {
                p1 = r + 1;
            }

            if(tolower((unsigned char)*p1) == tolower((unsigned char)*p2)) {
                r = p1;
                p2++;
            } else {
                r = 0;
            }
        }

        p1++;
    }

    return *p2 == 0 ? (char*)r : 0;
}

/**
 * Check if the given needle is present in the given haystack.
 * 
 * @param char* haystack The haystack to search in.
 * @param char* needle The needle to search for.
 * @param bool caseSensitive If a case sensitive check should be performed.
 * @param bool Positive if the needle was found in the haystack.
 */
bool stringContains(char* haystack, char* needle, bool caseSensitive) {
    return caseSensitive ? stringContainsCS(haystack, needle) : stringContainsCI(haystack, needle);
}