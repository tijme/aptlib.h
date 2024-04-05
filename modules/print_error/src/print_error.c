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
 * Standard Library.
 * 
 * Defines four variable types, several macros, and various functions for performing general functions.
 * https://www.tutorialspoint.com/c_standard_library/stdlib_h.htm
 */
#include <stdlib.h>

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
 * Local includes
 */
#include "../inc/print_error.h"

/**
 * Retrieve a human-readable string describing the given error code.
 * 
 * @param DWORD errorCode The error code to convert.
 * @param char* The human-readable output buffer.
 * @param DWORD The size of the output buffer.
 * @return DWORD The amount of bytes actually written.
 */
DWORD GetMessageFromError(DWORD errorCode, char* lpBuffer, DWORD size) {
    DWORD bytesWritten = FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
        NULL, 
        errorCode, 
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
        lpBuffer, 
        256, 
        NULL
    );

    if (bytesWritten > 0) {
        lpBuffer[bytesWritten -1] = 0x0; // remove newline
        return bytesWritten - 1;
    }

    return bytesWritten;
}

/**
 * Retrieve a human-readable string describing the last error code.
 * 
 * @param char* The human-readable output buffer.
 * @param DWORD The size of the output buffer.
 * @return DWORD The amount of bytes actually written.
 */
DWORD GetMessageFromLastError(char* lpBuffer, DWORD size) {
    return GetMessageFromError(GetLastError(), lpBuffer, size);
}

/**
 * Print a human-readable string, describing the given error code, to the console.
 * 
 * @param DWORD errorCode The error code to print a message for.
 */
void PrintMessageFromError(DWORD errorCode) {
    char* outputBuffer = calloc(256, sizeof(char));

    if(GetMessageFromError(errorCode, outputBuffer, 256)) {
        printf("[!] Error (0x%X, %d): %s\n", errorCode, errorCode, outputBuffer);
    } else {
        printf("[!] Error (0x%X, %d).\n", errorCode, errorCode);
    }

    free(outputBuffer);
}

/**
 * Print a human-readable string, describing the last error code, to the console.
 */
void PrintMessageFromLastError() {
    PrintMessageFromError(GetLastError());
}
