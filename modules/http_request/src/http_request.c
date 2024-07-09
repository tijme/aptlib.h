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
 * Booleans.
 * 
 * Defines boolean types.
 * https://pubs.opengroup.org/onlinepubs/007904975/basedefs/stdbool.h.html
 */
#include <stdbool.h>

/**
 * Integers.
 * 
 * Defines macros that specify limits of integer types corresponding to types defined in other standard headers.
 * https://pubs.opengroup.org/onlinepubs/009696899/basedefs/stdint.h.html
 */
#include <stdint.h>

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
 * Local includes
 */
#include "../inc/http_request.h"

/**
 * Perform an HTTP request based on the given parameters.
 * 
 * @param wchar_t* wHostname The domain (including subdomains) to connect to.
 * @param wchar_t* wPath The path (starting with /) to connect to.
 * @param DWORD nPort The TCP port to connect to.
 * @param bool bSecure If SSL/TLS must be used.
 * @param wchar_t* wMethod The HTTP request method (e.g. GET or POST).
 * @param wchar_t* wData Optional data that is sent with e.g. a POST or PUT request.
 * @param wchar_t* wUserAgent The user agent to use for the HTTP request.
 * @param HINTERNET* hSession A pointer to which the session handle will be stored.
 * @param HINTERNET* hRequest A pointer to which the request handle will be stored.
 * @return bool Positive if the request succeeded.
 */
bool HttpRequest(wchar_t* wHostname, wchar_t* wPath, DWORD nPort, bool bSecure, wchar_t* wMethod, wchar_t* wData, wchar_t* wUserAgent, HINTERNET* hSession, HINTERNET* hRequest) {
    HINTERNET hConnect;
    BOOL bStatus = false;

    *hSession = WinHttpOpen(wUserAgent, WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY, WINHTTP_NO_PROXY_BYPASS, WINHTTP_NO_PROXY_BYPASS, 0);
    if (*hSession == NULL) {
        goto CLEANUP_AND_RETURN;
    }

    hConnect = WinHttpConnect(*hSession, (LPCWSTR) wHostname, nPort, 0);
    if (hConnect == NULL) {
        goto CLEANUP_AND_RETURN;
    }

    *hRequest = WinHttpOpenRequest(hConnect, wMethod, wPath, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, (bSecure ? WINHTTP_FLAG_SECURE : 0));
    if (hRequest == NULL) {
        goto CLEANUP_AND_RETURN;
    }

    if (wData == NULL) {
        if (!WinHttpSendRequest(*hRequest, NULL, 0, NULL, 0, 0, 0)) {
            goto CLEANUP_AND_RETURN;
        }
    } else {
        if (!WinHttpSendRequest(*hRequest, L"content-type:application/x-www-form-urlencoded", -1, wData, wcslen(wData), wcslen(wData), 0)) {
            goto CLEANUP_AND_RETURN;
        }
    }

    if (!WinHttpReceiveResponse(*hRequest, NULL)) {
        goto CLEANUP_AND_RETURN;
    }

    bStatus = true;

CLEANUP_AND_RETURN:
    if (hConnect != NULL) WinHttpCloseHandle(hConnect);

RETURN:
    return bStatus;
}

/**
 * Perform an HTTP GET request based on the given parameters.
 * 
 * @param wchar_t* wHostname The domain (including subdomains) to connect to.
 * @param wchar_t* wPath The path (starting with /) to connect to.
 * @param DWORD nPort The TCP port to connect to.
 * @param bool bSecure If SSL/TLS must be used.
 * @param wchar_t* wUserAgent The user agent to use for the HTTP request.
 * @param HINTERNET* hSession A pointer to which the session handle will be stored.
 * @param HINTERNET* hRequest A pointer to which the request handle will be stored.
 * @return bool Positive if the request succeeded.
 */
bool HttpGetRequest(wchar_t* wHostname, wchar_t* wPath, DWORD nPort, bool bSecure, wchar_t* wUserAgent, HINTERNET* hSession, HINTERNET* hRequest) {
    return HttpRequest(wHostname, wPath, nPort, bSecure, L"GET", NULL, wUserAgent, hSession, hRequest);
}

/**
 * Perform an HTTP POST request based on the given parameters.
 * 
 * @param wchar_t* wHostname The domain (including subdomains) to connect to.
 * @param wchar_t* wPath The path (starting with /) to connect to.
 * @param DWORD nPort The TCP port to connect to.
 * @param bool bSecure If SSL/TLS must be used.
 * @param wchar_t* wData Optional data that is sent with the POST request.
 * @param wchar_t* wUserAgent The user agent to use for the HTTP request.
 * @param HINTERNET* hSession A pointer to which the session handle will be stored.
 * @param HINTERNET* hRequest A pointer to which the request handle will be stored.
 * @return bool Positive if the request succeeded.
 */
bool HttpPostRequest(wchar_t* wHostname, wchar_t* wPath, DWORD nPort, bool bSecure, wchar_t* wData, wchar_t* wUserAgent, HINTERNET* hSession, HINTERNET* hRequest) {
    return HttpRequest(wHostname, wPath, nPort, bSecure, L"POST", wData, wUserAgent, hSession, hRequest);
}

/**
 * Retrieve the HTTP response status of the given request handle.
 * 
 * @param HINTERNET* hRequest A valid pointer to an open request handle.
 * @param DWORD* lpdwResponseStatus The obtained HTTP response status.
 * @return bool Positive if the retrieval succeeded.
 */
bool getHttpResponseStatus(HINTERNET hRequest, DWORD* lpdwResponseStatus) {
    BOOL bStatus = false;
    DWORD dwResponseStatusSize = sizeof(DWORD);

    if (!WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, NULL, lpdwResponseStatus, &dwResponseStatusSize, NULL)) {
        goto RETURN;
    }

    bStatus = true;

RETURN:
    return bStatus;
}

/**
 * Retrieve the HTTP response body of the given request handle.
 * 
 * @param HINTERNET* hRequest A valid pointer to an open request handle.
 * @param uint8_t** lpResponseBody The obtained HTTP response body.
 * @return bool Positive if the retrieval succeeded.
 */
bool getHttpResponseBody(HINTERNET hRequest, uint8_t** lpResponseBody) {
    BOOL bStatus = false;
    DWORD dwNumberOfBytesToRead = 0;
    DWORD dwNumberOfBytesRead = 0;
    DWORD dwResponseBodySize = 0;
    *lpResponseBody = NULL;

    do {
        if (!WinHttpQueryDataAvailable(hRequest, &dwNumberOfBytesToRead)) {
            goto CLEANUP_AND_RETURN;
        }

        if (dwNumberOfBytesToRead == 0) {
            goto SUCCESS_AND_RETURN;
        }

        *lpResponseBody = realloc(*lpResponseBody, dwResponseBodySize + dwNumberOfBytesToRead);
   
        if(!WinHttpReadData(hRequest, *lpResponseBody + dwResponseBodySize, dwNumberOfBytesToRead, &dwNumberOfBytesRead)) {
            goto CLEANUP_AND_RETURN;
        }

        dwResponseBodySize = dwResponseBodySize + dwNumberOfBytesRead;
    } while (dwNumberOfBytesRead > 0);

SUCCESS_AND_RETURN:
    bStatus = true;
    goto RETURN;

CLEANUP_AND_RETURN:
    if (*lpResponseBody != NULL) free(*lpResponseBody);

RETURN:
    return bStatus;
}

