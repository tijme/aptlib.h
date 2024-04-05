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
 * Check if the given affix indeed ends with in the given string (case sensitive).
 * 
 * @param char* string The string to check the affix for.
 * @param char* possibleAffix The affix to search for.
 * @param bool caseSensitive If a case sensitive check should be performed.
 * @param bool Positive if the string is affixed with the possible affix.
 */
bool stringEndsWithCS(char* string, char* possibleAffix);

/**
 * Check if the given affix is indeed a affix in the given string (case insensitive).
 * 
 * @param char* string The string to check the affix for.
 * @param char* possibleAffix The affix to search for.
 * @param bool caseSensitive If a case sensitive check should be performed.
 * @param bool Positive if the string is affixed with the possible affix.
 */
bool stringEndsWithCI(char* string, char* possibleAffix);

/**
 * Check if the given affix is indeed a affix in the given string.
 * 
 * @param char* string The string to check the affix for.
 * @param char* possibleAffix The affix to search for.
 * @param bool caseSensitive If a case sensitive check should be performed.
 * @param bool Positive if the string is affixed with the possible affix.
 */
bool stringEndsWith(char* string, char* possibleAffix, bool caseSensitive);