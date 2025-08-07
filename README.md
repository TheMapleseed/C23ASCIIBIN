# ASCIIBIN

A modular C library for converting between ASCII text and 7-bit binary representation.

## Features

- **Modular Design**: Clean separation of concerns with dedicated modules
- **C23 Compliance**: Full compliance with the latest C standard
- **Error Handling**: Comprehensive error codes and validation
- **Memory Safe**: Proper allocation/deallocation with overflow protection
- **Documentation**: Complete Doxygen-style documentation

## Project Structure

```
ASCIIBIN/
├── asciibin.h          # Main library interface
├── asciibin.c          # Core implementation
├── lookup_table.h      # Lookup table interface
├── lookup_table.c      # Lookup table implementation
├── main.c             # Demo application
├── Makefile           # Build system
└── README.md          # This file
```

## Building

```bash
# Build the project
make

# Build with debug symbols
make debug

# Build optimized release version
make release

# Build with address sanitizer for testing
make test-asan

# Clean build artifacts
make clean

# Run the demo
make run
```

## Usage

The library provides functions for converting between ASCII characters and their 7-bit binary representations:

```c
#include "asciibin.h"

// Convert text to binary
size_t binary_length;
char* binary = convert_text_to_binary("Hello", &binary_length);

// Convert binary back to text
char* text = convert_binary_to_text(binary, binary_length);

// Clean up
free(binary);
free(text);
```

## Error Handling

The library uses comprehensive error codes:

```c
ASCIIBIN_ErrorCode result = ascii_to_binary_char('A', buffer);
if (result != ASCIIBIN_SUCCESS) {
    printf("Error: %s\n", asciibin_get_error_message(result));
}
```

## License

This project follows clean code principles and modular design patterns for maintainable, testable, and extensible C code.