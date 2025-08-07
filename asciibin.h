/**
 * @file asciibin.h
 * @brief ASCII to Binary conversion library
 * @author ASCIIBIN Project
 * @version 1.0
 * @date 2025
 * 
 * This library provides functions to convert between ASCII text and 7-bit binary
 * representation. It follows clean code principles and modular design patterns.
 */

#ifndef ASCIIBIN_H
#define ASCIIBIN_H

#include <stddef.h>

/**
 * @brief Error codes for ASCIIBIN operations
 */
typedef enum {
    ASCIIBIN_SUCCESS = 0,           /**< Operation completed successfully */
    ASCIIBIN_ERROR_NULL_POINTER,    /**< NULL pointer provided */
    ASCIIBIN_ERROR_INVALID_INPUT,   /**< Invalid input format */
    ASCIIBIN_ERROR_MEMORY,          /**< Memory allocation failed */
    ASCIIBIN_ERROR_NOT_FOUND        /**< Character not found in lookup table */
} ASCIIBIN_ErrorCode;

/**
 * @brief Convert a single ASCII character to its 7-bit binary representation
 * 
 * @param ascii_char The ASCII character to convert
 * @param binary_buffer Buffer to store the binary string (must be at least 8 chars)
 * @return ASCIIBIN_ErrorCode Success or error code
 * 
 * @note The binary string will be null-terminated and exactly 7 characters long
 */
ASCIIBIN_ErrorCode ascii_to_binary_char(char ascii_char, char* binary_buffer);

/**
 * @brief Convert a 7-bit binary string to its ASCII character representation
 * 
 * @param binary_string The 7-bit binary string to convert
 * @param ascii_char Pointer to store the resulting ASCII character
 * @return ASCIIBIN_ErrorCode Success or error code
 * 
 * @note The binary string must be exactly 7 characters long and contain only '0' and '1'
 */
ASCIIBIN_ErrorCode binary_to_ascii_char(const char* binary_string, char* ascii_char);

/**
 * @brief Convert a text string to its binary representation
 * 
 * @param text Input text string to convert
 * @param binary_length Pointer to store the length of the resulting binary string
 * @return char* Dynamically allocated binary string, or NULL on error
 * 
 * @note The caller is responsible for freeing the returned string
 */
char* convert_text_to_binary(const char* text, size_t* binary_length);

/**
 * @brief Convert a binary string back to text
 * 
 * @param binary Binary string to convert
 * @param binary_length Length of the binary string
 * @return char* Dynamically allocated text string, or NULL on error
 * 
 * @note The caller is responsible for freeing the returned string
 */
char* convert_binary_to_text(const char* binary, size_t binary_length);

/**
 * @brief Get a human-readable error message
 * 
 * @param error_code The error code to convert
 * @return const char* Human-readable error message
 */
const char* asciibin_get_error_message(ASCIIBIN_ErrorCode error_code);

/**
 * @brief Validate if a string contains only valid binary characters
 * 
 * @param binary_string String to validate
 * @param length Length of the string
 * @return int 1 if valid, 0 if invalid
 */
int is_valid_binary_string(const char* binary_string, size_t length);

#endif /* ASCIIBIN_H */ 
