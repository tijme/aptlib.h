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
 * Integers.
 * 
 * Defines macros that specify limits of integer types corresponding to types defined in other standard headers.
 * https://pubs.opengroup.org/onlinepubs/009696899/basedefs/stdint.h.html
 */
#include <stdint.h>

/**
 * Booleans.
 * 
 * Defines boolean types.
 * https://pubs.opengroup.org/onlinepubs/007904975/basedefs/stdbool.h.html
 */
#include <stdbool.h>
 
/**
 * Check if the given haystack starts with the given byte/match sequence.
 * 
 * @param char* haystack A byte sequence to search in (e.g. `ntoskrnl.exe` memory).
 * @param char* needle A byte sequence (egg) to search for (e.g. `\x8B\x42\x00\x00\x00\xB7\xC9`)
 * @param char* mask Which bytes must match in the image (e.g. `xx???xx`).
 * @return bool Positive if it is a match, negative otherwise.
 */
bool byteSequenceStartsWithByteSequence(uint8_t* haystack, uint8_t* needle, uint8_t* mask);

/**
 * Find offset of exported functions via `GetProcAddress`.
 * 
 * @param char* imageName The name of the image to load (e.g. `ntoskrnl.exe`).
 * @param char* exportName Which function name to get the offset for.
 * @return uint64_t The offset to the function if found. Zero otherwise.
 */
uint64_t findFunctionOffsetByExport(char* imageName, char* exportName);

/**
 * Find offset of unexported functions via some sort of egg hunting (byte sequence search).
 * 
 * Note:
 * Let's say you have a byte sequence of `\x8B\x42 ? ? ? \xB7\xC9` in "ntoskrnl.exe" of which the first two and last two 
 * bytes are static, and the middle three are different depending on OS version. Then you can call this function as follows:
 * findFunctionOffsetInImageByByteSequence("ntoskrnl.exe", "\x8B\x42\x00\x00\x00\xB7\xC9", "xx???xx");
 * 
 * @param char* imageName The name of the image to load (e.g. `ntoskrnl.exe`).
 * @param char* needle A byte sequence (egg) to search for (e.g. `\x8B\x42\x00\x00\x00\xB7\xC9`)
 * @param char* mask Which bytes must match in the image (e.g. `xx???xx`).
 * @return uint64_t The offset to the function if found. Zero otherwise.
 */
uint64_t findFunctionOffsetInImageByByteSequence(char* imageName, char* needle, char* mask);