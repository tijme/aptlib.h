/**
 * Standard Input Output.
 * 
 * Defines three variable types, several macros, and various functions for performing input and output.
 * https://www.tutorialspoint.com/c_standard_library/stdio_h.htm
 */
#include <stdio.h>

/**
 * Include custom header files.
 */
#include "inc/print_error.h"

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

    puts("[+] Starting checks for module `print_error`.");

    PrintMessageFromError(0xC026233F);

    puts("[+] Finished checks for module `print_error`.");
}

