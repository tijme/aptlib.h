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
 * Internal NT API's and data structures.
 * 
 * Helper library that contains NT API's and data structures for system services, security and identity.
 * https://docs.microsoft.com/en-us/windows/win32/api/winternl/
 */
#include <winternl.h>

/**
 * Local includes
 */
#include "../inc/get_image_base.h"

/**
 * Get the virtual address base from the given image.
 * 
 * @return LPVOID A pointer to the image base in the system space.
 */
LPVOID getImageBase(LPCSTR imageName) {
    DWORD dwSize = 0;

    if (NtQuerySystemInformation(SystemModuleInformation, NULL, dwSize, &dwSize) != STATUS_INFO_LENGTH_MISMATCH) {
        return NULL;
    }
  
    PRTL_PROCESS_MODULES pSystemModules = (PRTL_PROCESS_MODULES) GlobalAlloc(GMEM_ZEROINIT, dwSize);
    
    if (!pSystemModules) {
        return NULL;
    }

    if (!NT_SUCCESS(NtQuerySystemInformation(SystemModuleInformation, pSystemModules, dwSize, &dwSize))) {
        GlobalFree(pSystemModules);
        return NULL;
    }

    DWORD dwCount = pSystemModules->NumberOfModules;
    
    for (DWORD i = 0; i < dwCount; i++) {
        if (strstr((char*) pSystemModules->Modules[i].FullPathName, imageName)) {
            LPVOID pBase = (LPVOID) pSystemModules->Modules[i].ImageBase;
            GlobalFree(pSystemModules);
            return pBase;
        }
    }

    GlobalFree(pSystemModules);
    return NULL;
}