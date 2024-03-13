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
#include "inc/string_is_prefixed.h"

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

    puts("[+] Starting checks for module `string_is_prefixed`.");

    char* thePrefix = "This";
    char* thePrefixLower = "this";
    char* notThePrefix = "Not";
    char* string = "This is a test message!";

    // Case sensitive; prefixed
    if (stringIsPrefixed(string, thePrefix, true)) {
        puts("[+] CHECK1: Succesfully completed.");
    } else {
        puts("[!] CHECK1: Failed to perform 'string contains' operation.");
    }

    // Case sensitive; not prefixed
    if (stringIsPrefixed(string, notThePrefix, true)) {
        puts("[!] CHECK2: Failed to perform 'string contains' operation.");
    } else {
        puts("[+] CHECK2: Succesfully completed.");
    }

    // Case sensitive; case sensitive prefixed
    if (stringIsPrefixed(string, thePrefixLower, true)) {
        puts("[!] CHECK3: Failed to perform 'string contains' operation.");
    } else {
        puts("[+] CHECK3: Succesfully completed.");
    }

    // Case insensitive; prefixed
    if (stringIsPrefixed(string, thePrefixLower, false)) {
        puts("[+] CHECK4: Succesfully completed.");
    } else {
        puts("[!] CHECK4: Failed to perform 'string contains' operation.");
    }

    // Case insensitive; not prefixed
    if (stringIsPrefixed(string, notThePrefix, false)) {
        puts("[!] CHECK5: Failed to perform 'string contains' operation.");
    } else {
        puts("[+] CHECK5: Succesfully completed.");
    }

    // // Case sensitive; does not contain
    // if (stringIsPrefixed(string, possiblePrefixLower, true)) {
    //     puts("[!] CHECK2: Failed to perform 'string contains' operation.");
    // } else {
    //     puts("[+] CHECK2: Succesfully completed.");
    // }
    
    puts("[+] Finished checks for module `string_is_prefixed`.");
}

