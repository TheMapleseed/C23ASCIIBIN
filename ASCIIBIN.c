/**
 * @file asciibin.c
 * @brief Implementation of ASCII to Binary conversion library
 */

#include "asciibin.h"
#include "lookup_table.h"
#include <stdlib.h>
#include <string.h>

/* Error messages */
static const char* error_messages[] = {
    "Success",
    "NULL pointer provided",
    "Invalid input format",
    "Memory allocation failed",
    "Character not found in lookup table"
};

const char* asciibin_get_error_message(ASCIIBIN_ErrorCode error_code) {
    if (error_code >= 0 && error_code < sizeof(error_messages) / sizeof(char*)) {
        return error_messages[error_code];
    }
    return "Unknown error";
}

int is_valid_binary_string(const char* binary_string, size_t length) {
    if (binary_string == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < length; i++) {
        if (binary_string[i] != '0' && binary_string[i] != '1') {
            return 0;
        }
    }
    
    return 1;
}

ASCIIBIN_ErrorCode ascii_to_binary_char(char ascii_char, char* binary_buffer) {
    if (binary_buffer == NULL) {
        return ASCIIBIN_ERROR_NULL_POINTER;
    }
    
    if (find_ascii_in_table(ascii_char, binary_buffer)) {
        return ASCIIBIN_SUCCESS;
    }
    
    return ASCIIBIN_ERROR_NOT_FOUND;
}

ASCIIBIN_ErrorCode binary_to_ascii_char(const char* binary_string, char* ascii_char) {
    if (binary_string == NULL || ascii_char == NULL) {
        return ASCIIBIN_ERROR_NULL_POINTER;
    }
    
    /* Validate binary string format */
    if (strlen(binary_string) != 7) {
        return ASCIIBIN_ERROR_INVALID_INPUT;
    }
    
    if (!is_valid_binary_string(binary_string, 7)) {
        return ASCIIBIN_ERROR_INVALID_INPUT;
    }
    
    if (find_binary_in_table(binary_string, ascii_char)) {
        return ASCIIBIN_SUCCESS;
    }
    
    return ASCIIBIN_ERROR_NOT_FOUND;
}

char* convert_text_to_binary(const char* text, size_t* binary_length) {
    if (text == NULL || binary_length == NULL) {
        return NULL;
    }
    
    const size_t text_length = strlen(text);
    
    /* Check for potential integer overflow */
    if (text_length > SIZE_MAX / 7) {
        return NULL;
    }
    
    const size_t required_length = 7 * text_length;
    char* binary = (char*)malloc(required_length + 1);
    if (binary == NULL) {
        return NULL;
    }
    
    binary[required_length] = '\0';
    
    /* Convert each character */
    for (size_t i = 0; i < text_length; i++) {
        char binary_char[8];
        ASCIIBIN_ErrorCode result = ascii_to_binary_char(text[i], binary_char);
        
        if (result != ASCIIBIN_SUCCESS) {
            free(binary);
            return NULL;
        }
        
        strncpy(&binary[i * 7], binary_char, 7);
    }
    
    *binary_length = required_length;
    return binary;
}

char* convert_binary_to_text(const char* binary, size_t binary_length) {
    if (binary == NULL) {
        return NULL;
    }
    
    /* Validate binary length is divisible by 7 */
    if (binary_length % 7 != 0) {
        return NULL;
    }
    
    /* Validate binary string contains only '0' and '1' */
    if (!is_valid_binary_string(binary, binary_length)) {
        return NULL;
    }
    
    const size_t text_length = binary_length / 7;
    char* text = (char*)malloc(text_length + 1);
    if (text == NULL) {
        return NULL;
    }
    
    text[text_length] = '\0';
    
    /* Convert each 7-bit sequence */
    for (size_t i = 0; i < text_length; i++) {
        char binary_char[8];
        strncpy(binary_char, &binary[i * 7], 7);
        binary_char[7] = '\0';
        
        ASCIIBIN_ErrorCode result = binary_to_ascii_char(binary_char, &text[i]);
        if (result != ASCIIBIN_SUCCESS) {
            free(text);
            return NULL;
        }
    }
    
    return text;
}
