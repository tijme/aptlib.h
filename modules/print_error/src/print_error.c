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
 * Define 'WIN32_LEAN_AND_MEAN' to make sure windows.h compiles without warnings.
 * https://docs.microsoft.com/en-us/previous-versions//aa383749(v=vs.85)?redirectedfrom=MSDN
 */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/**
 * Retrieve a human-readable string describing the given error code.
 * 
 * @param DWORD errorCode The error code to convert.
 * @param char* The human-readable output buffer.
 * @param DWORD The size of the output buffer.
 * @returns DWORD The amount of bytes actually written.
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
 * @returns DWORD The amount of bytes actually written.
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
