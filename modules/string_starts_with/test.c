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
 * Standard Input Output.
 * 
 * Defines three variable types, several macros, and various functions for performing input and output.
 * https://www.tutorialspoint.com/c_standard_library/stdio_h.htm
 */
#include <stdio.h>

/**
 * Strings.
 * 
 * Defines one variable type, one macro, and various functions for manipulating arrays of characters.
 * https://www.tutorialspoint.com/c_standard_library/string_h.htm
 */
#include <string.h>

/**
 * Include custom header files.
 */
#include "inc/string_starts_with.h"

/**
 * Default defines
 */
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(parameter) (parameter)
#endif

/**
 * Test the current module.
 *
 * @param int argc Amount of arguments in `argv`.
 * @param char** argv Array of arguments passed to the program.
 * @param char** envp Array of environent key=value char arrays.
 */
int main(int argc, char** argv, char **envp) {
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(argv);

    puts("[+] Starting checks for module `string_starts_with`.");

    char* thePrefix = "This";
    char* thePrefixLower = "this";
    char* notThePrefix = "Not";
    char* string = "This is a test message!";

    // Case sensitive; prefixed
    if (stringStartsWith(string, thePrefix, true)) {
        puts("[+] CHECK1: Succesfully completed.");
    } else {
        puts("[!] CHECK1: Failed to perform 'string starts with' operation.");
    }

    // Case sensitive; not prefixed
    if (stringStartsWith(string, notThePrefix, true)) {
        puts("[!] CHECK2: Failed to perform 'string starts with' operation.");
    } else {
        puts("[+] CHECK2: Succesfully completed.");
    }

    // Case sensitive; case sensitive prefixed
    if (stringStartsWith(string, thePrefixLower, true)) {
        puts("[!] CHECK3: Failed to perform 'string starts with' operation.");
    } else {
        puts("[+] CHECK3: Succesfully completed.");
    }

    // Case insensitive; prefixed
    if (stringStartsWith(string, thePrefixLower, false)) {
        puts("[+] CHECK4: Succesfully completed.");
    } else {
        puts("[!] CHECK4: Failed to perform 'string starts with' operation.");
    }

    // Case insensitive; not prefixed
    if (stringStartsWith(string, notThePrefix, false)) {
        puts("[!] CHECK5: Failed to perform 'string starts with' operation.");
    } else {
        puts("[+] CHECK5: Succesfully completed.");
    }
    
    puts("[+] Finished checks for module `string_starts_with`.");
}

