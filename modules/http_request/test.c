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
 * Windows API.
 * 
 * Contains declarations for all of the functions, macro's & data types in the Windows API.
 * https://docs.microsoft.com/en-us/previous-versions//aa383749(v=vs.85)?redirectedfrom=MSDN
 */
#include <windows.h>

/**
 * Used by the Windows HTTP services.
 * 
 * Contains manifests, macros, types and prototypes for Windows HTTP Services.
 * https://learn.microsoft.com/en-us/windows/win32/api/winhttp/
 */
#include <winhttp.h>
#pragma comment(lib, "Winhttp.lib")

/**
 * Include custom header files.
 */
#include "inc/http_request.h"

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

    puts("[+] Starting checks for module `http_request`.");

    HINTERNET hSession;
    HINTERNET hRequest;
    if (HttpGetRequest(L"tij.me", L"/", 443, true, NULL, &hSession, &hRequest)) {
        puts("[+] CHECK1: Succesfully completed.");
    } else {
        printf("[!] CHECK1: Failed to perform 'HttpGetRequest' operation: 0x%X.\n", GetLastError());
        return 1;
    }

    DWORD dwResponseStatus;
    if (getHttpResponseStatus(hRequest, &dwResponseStatus) && dwResponseStatus == 200) {
        printf("[+] CHECK2: Succesfully completed.\n", dwResponseStatus);
    } else {
        printf("[!] CHECK2: Failed to perform 'getHttpResponseStatus' operation: 0x%X.\n", GetLastError());
        return 1;
    }

    uint8_t* lpResponseBody;
    if (getHttpResponseBody(hRequest, &lpResponseBody)) {
        puts("[+] CHECK3: Succesfully completed.");
    } else {
        printf("[!] CHECK3: Failed to perform 'getHttpResponseBody' operation: 0x%X.\n", GetLastError());
        return 1;
    }

    if (strstr(lpResponseBody, "Tijme Gommers") != NULL) {
        puts("[+] CHECK4: Succesfully completed.");
    } else {
        printf("[!] CHECK4: Failed to find 'Tijme Gommers' in response body.\n", GetLastError());
        return 1;
    }

    WinHttpCloseHandle(hSession);
    WinHttpCloseHandle(hRequest);

    puts("[+] Finished checks for module `http_request`.");
}

