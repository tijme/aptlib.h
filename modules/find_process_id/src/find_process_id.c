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
 * Windows API.
 * 
 * Contains declarations for all of the functions, macro's & data types in the Windows API.
 * Define 'WIN32_LEAN_AND_MEAN' to make sure windows.h compiles without warnings.
 * https://docs.microsoft.com/en-us/previous-versions//aa383749(v=vs.85)?redirectedfrom=MSDN
 */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/**
 * Tool Help Library
 * 
 * WIN32 tool help functions, types, and definitions.
 * https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/
 */
#include <tlhelp32.h>

/**
 * Booleans.
 * 
 * Defines boolean types.
 * https://pubs.opengroup.org/onlinepubs/007904975/basedefs/stdbool.h.html
 */
#include <stdbool.h>

/**
 * Local includes
 */
#include "../inc/find_process_id.h"

/**
 * Find a process ID by process name.
 * 
 * @param char* processName The name of the process to search for.
 * @param DWORD* processID Output parameter for the ID of the process.
 * @return bool Positive if PID was found succesfully.
 */
bool FindProcessIDByProcessName(char* processName, DWORD* processID) {
    PROCESSENTRY32 processEntry;
    HANDLE hSnapshot;
    BOOL hResult;

    // Initialize processID to 0
    *processID = -1;

    // Create snapshot of all running processes
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return false;
    }

    // Initializing size, needed for using Process32First
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    // Information about the first process encountered in the snapshot
    hResult = Process32First(hSnapshot, &processEntry);

    // Iterate all processes in the snapshot
    while (hResult) {
        if (strcmp(processName, processEntry.szExeFile) == 0) {
            *processID = processEntry.th32ProcessID;
            break;
        }

        hResult = Process32Next(hSnapshot, &processEntry);
    }

    // Close snapshot handle, return if we found the process
    CloseHandle(hSnapshot);

    // Return positive if a process ID was identified
    return *processID != -1;
}