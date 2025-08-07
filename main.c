/**
 * @file main.c
 * @brief Main application demonstrating ASCIIBIN library usage
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asciibin.h"

/**
 * @brief Demonstrate single character conversion
 */
void demonstrate_single_char_conversion(void) {
    printf("=== Single Character Conversion Demo ===\n");
    
    char test_chars[] = {'A', '!', '5', 'z', ' '};
    const int num_chars = sizeof(test_chars) / sizeof(char);
    
    for (int i = 0; i < num_chars; i++) {
        char binary_buffer[8];
        ASCIIBIN_ErrorCode result = ascii_to_binary_char(test_chars[i], binary_buffer);
        
        if (result == ASCIIBIN_SUCCESS) {
            printf("'%c' -> %s\n", test_chars[i], binary_buffer);
            
            /* Test reverse conversion */
            char ascii_char;
            result = binary_to_ascii_char(binary_buffer, &ascii_char);
            if (result == ASCIIBIN_SUCCESS) {
                printf("  %s -> '%c' ✓\n", binary_buffer, ascii_char);
            }
        } else {
            printf("'%c' -> Error: %s\n", test_chars[i], asciibin_get_error_message(result));
        }
    }
    printf("\n");
}

/**
 * @brief Demonstrate text string conversion
 */
void demonstrate_text_conversion(void) {
    printf("=== Text String Conversion Demo ===\n");
    
    const char* test_strings[] = {
        "Hello, World!",
        "ASCII",
        "12345",
        "!@#$%",
        "A\nB\tC",
        ""
    };
    
    const int num_strings = sizeof(test_strings) / sizeof(char*);
    
    for (int i = 0; i < num_strings; i++) {
        printf("Original: '%s'\n", test_strings[i]);
        
        size_t binary_length;
        char* binary = convert_text_to_binary(test_strings[i], &binary_length);
        
        if (binary != NULL) {
            printf("Binary:   %s\n", binary);
            
            char* converted = convert_binary_to_text(binary, binary_length);
            if (converted != NULL) {
                printf("Converted: '%s' ✓\n", converted);
                free(converted);
            } else {
                printf("Converted: Error\n");
            }
            
            free(binary);
        } else {
            printf("Binary:   Error\n");
        }
        printf("\n");
    }
}

/**
 * @brief Demonstrate error handling
 */
void demonstrate_error_handling(void) {
    printf("=== Error Handling Demo ===\n");
    
    /* Test NULL pointer handling */
    char* result = convert_text_to_binary(NULL, NULL);
    printf("NULL input test: %s\n", result == NULL ? "PASS" : "FAIL");
    
    /* Test invalid binary string */
    char ascii_char;
    ASCIIBIN_ErrorCode error = binary_to_ascii_char("1010102", &ascii_char);
    printf("Invalid binary '1010102': %s\n", asciibin_get_error_message(error));
    
    /* Test wrong length binary */
    error = binary_to_ascii_char("10101", &ascii_char);
    printf("Wrong length '10101': %s\n", asciibin_get_error_message(error));
    
    /* Test invalid characters */
    error = binary_to_ascii_char("10101ab", &ascii_char);
    printf("Invalid chars '10101ab': %s\n", asciibin_get_error_message(error));
    
    printf("\n");
}

/**
 * @brief Demonstrate binary string validation
 */
void demonstrate_validation(void) {
    printf("=== Binary String Validation Demo ===\n");
    
    const char* test_binaries[] = {
        "1010101",  /* Valid */
        "0000000",  /* Valid */
        "1111111",  /* Valid */
        "1010102",  /* Invalid - contains '2' */
        "10101ab",  /* Invalid - contains letters */
        "101010",   /* Invalid - wrong length */
        "10101010"  /* Invalid - wrong length */
    };
    
    const int num_tests = sizeof(test_binaries) / sizeof(char*);
    
    for (int i = 0; i < num_tests; i++) {
        int is_valid = is_valid_binary_string(test_binaries[i], strlen(test_binaries[i]));
        printf("'%s': %s\n", test_binaries[i], is_valid ? "Valid" : "Invalid");
    }
    printf("\n");
}

int main(void) {
    printf("ASCIIBIN Library Demo\n");
    printf("=====================\n\n");
    
    demonstrate_single_char_conversion();
    demonstrate_text_conversion();
    demonstrate_error_handling();
    demonstrate_validation();
    
    printf("Demo completed successfully!\n");
    return 0;
} 
