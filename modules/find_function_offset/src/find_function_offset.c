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
 * Process Status API (PSAPI).
 * 
 * Helper library that makes it easier for you to obtain information about processes and device drivers. 
 * https://docs.microsoft.com/en-us/windows/win32/api/psapi/
 */
#include <psapi.h>

/**
 * Local includes
 */
#include "../inc/find_function_offset.h"

/**
 * Check if the given haystack starts with the given byte/match sequence.
 * 
 * @param char* haystack A byte sequence to search in (e.g. `ntoskrnl.exe` memory).
 * @param char* needle A byte sequence (egg) to search for (e.g. `\x8B\x42\x00\x00\x00\xB7\xC9`)
 * @param char* mask Which bytes must match in the image (e.g. `xx???xx`).
 * @return bool Positive if it is a match, negative otherwise.
 */
bool byteSequenceStartsWithByteSequence(uint8_t* haystack, uint8_t* needle, uint8_t* mask) {
    size_t i;

    for (i = 0; i < strlen(mask); i++) {
        if(mask[i] == 'x' && haystack[i] != needle[i]) {
            return 0;
        }
    }

    return i == strlen(mask);
}

/**
 * Find offset of exported functions via `GetProcAddress`.
 * 
 * @param char* imageName The name of the image to load (e.g. `ntoskrnl.exe`).
 * @param char* exportName Which function name to get the offset for.
 * @return uint64_t The offset to the function if found. Zero otherwise.
 */
uint64_t findFunctionOffsetByExport(char* imageName, char* exportName) {
    HANDLE hImage = LoadLibraryExA(imageName, NULL, DONT_RESOLVE_DLL_REFERENCES);
    if (hImage == NULL) {
        return 0;
    }
    
    LPVOID hExport = (LPVOID) GetProcAddress(hImage, exportName);
    if (hExport == NULL) {
        return 0;
    }

    return (uint64_t) (((uintptr_t) hExport) - ((uintptr_t) hImage));
}

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
uint64_t findFunctionOffsetInImageByByteSequence(char* imageName, char* needle, char* mask) {
    uint64_t result = 0;

    HMODULE hModule = LoadLibraryExA(imageName, NULL, DONT_RESOLVE_DLL_REFERENCES);
    if(hModule == NULL) {
        goto CLEANUP_AND_RETURN;
    }

    // Retrieve information about the loaded module
    MODULEINFO modinfo;
    bool gotModuleInformation = GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(modinfo));
    if (!gotModuleInformation) {
        goto CLEANUP_AND_RETURN;
    }

    // Number of bytes to read from memory
    size_t nNumberOfBytesToRead = (size_t) modinfo.SizeOfImage;

    // Allocate memory for bytes to read and a null termination
    uint8_t* bytes = calloc(nNumberOfBytesToRead, sizeof(uint8_t));

    // Define how many bytes have been read
    size_t* lpNumberOfBytesRead = 0;

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, false, GetCurrentProcessId());
    if(hProcess == NULL) {
        goto CLEANUP_AND_RETURN;
    }

    if(!ReadProcessMemory(hProcess, modinfo.lpBaseOfDll, bytes, nNumberOfBytesToRead, lpNumberOfBytesRead)) {
        goto CLEANUP_AND_RETURN;
    }

    for (size_t i = 0; i < modinfo.SizeOfImage; i ++) {
        if (byteSequenceStartsWithByteSequence(bytes + i, needle, mask)) {
            result = (uint64_t) i;
            goto CLEANUP_AND_RETURN;
        }
    }

CLEANUP_AND_RETURN:
    if (hProcess != NULL) CloseHandle(hProcess);
    return result;
}