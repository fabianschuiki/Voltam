library-development
===================
A tool used to develop the library codebase.

Approach
--------
The library consists of scripts and tables that all define symbols, packages and entire devices. Scripts may synthesize multiple devices that are similar, e.g. the ATtiny13 MCU comes in about 15 variants that are all similar. The scripts *do not copy inheritance, package and symbol information* for every device, but create *links* to them. This ensures that the library can be loaded quickly without repeating common information.