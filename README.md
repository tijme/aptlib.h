<p align="center">
    <img src="https://raw.githubusercontent.com/tijme/aptlib.h/master/.github/logo.png" width="600"/>
</p>
<p align="center">
    <a href="https://github.com/tijme/aptlib.h/blob/master/LICENSE.md"><img src="https://img.shields.io/badge/Source-Licensed-da0024?style=for-the-badge" /></a>
    <br/>
    <b>A standard c-code library (<code>aptlib.h</code>) for exploit & malware development.</b>
    <br/>
    <sup>Built with ♥ by <a href="https://www.linkedin.com/in/tijme/">Tijme Gommers</a> – Buy me a coffee via <a href="https://www.paypal.me/tijmegommers">PayPal</a>.</sup>
    <br/>
</p>

## Background

Whilst developing exploits and malware, I often encountered code redundancy throughout my projects. This led to the creation of `aptlib.h`, as a response to the recurring need for functionalities like retrieving user information, querying processes, managing static offsets, and more. `aptlib.h` is a high cohesion & low coupling c-code library that can be easily integrated in any c-code project through a Git submodule. Whether you're delving into malware development, crafting exploits, or pursuing other endeavors; it helps you stay one step ahead of APT's.

## Usage

Add this repository as submodule to your repository:

    git submodule add git@github.com:tijme/aptlib.h.git vendor/aptlib

Compile `aptlib.h` through your makefile:

    ACTION=objects make -C vendor/aptlib

Use the objects in your makefile:

    gcc ./vendor/aptlib/modules/print_in_hex/print_in_hex.o ./test.c -o test.exe

## Issues

Issues or new features can be reported via the [issue tracker](https://github.com/tijme/aptlib.h/issues). Please make sure your issue or feature has not yet been reported by anyone else before submitting a new one.

## License

Copyright (c) 2024 Tijme Gommers. All rights reserved. View [LICENSE.md](https://github.com/tijme/aptlib.h/blob/master/LICENSE.md) for the full license.