/**
 * @file lookup_table.h
 * @brief ASCII to Binary lookup table module
 * 
 * This module provides the lookup table for converting between ASCII characters
 * and their 7-bit binary representations. It encapsulates the data structure
 * and provides clean interfaces for table operations.
 */

#ifndef LOOKUP_TABLE_H
#define LOOKUP_TABLE_H

#include <stddef.h>

/**
 * @brief Structure representing an ASCII-binary mapping entry
 */
typedef struct {
    char binary[8];  /**< 7-bit binary string + null terminator */
    char ascii[2];   /**< ASCII character + null terminator */
} LookupEntry;

/**
 * @brief Get the total number of entries in the lookup table
 * 
 * @return size_t Number of entries
 */
size_t get_lookup_table_size(void);

/**
 * @brief Get a pointer to the lookup table
 * 
 * @return const LookupEntry* Pointer to the lookup table
 */
const LookupEntry* get_lookup_table(void);

/**
 * @brief Find binary representation for an ASCII character
 * 
 * @param ascii_char The ASCII character to find
 * @param binary_buffer Buffer to store the binary string (must be at least 8 chars)
 * @return int 1 if found, 0 if not found
 */
int find_ascii_in_table(char ascii_char, char* binary_buffer);

/**
 * @brief Find ASCII character for a binary string
 * 
 * @param binary_string The 7-bit binary string to find
 * @param ascii_char Pointer to store the ASCII character
 * @return int 1 if found, 0 if not found
 */
int find_binary_in_table(const char* binary_string, char* ascii_char);

#endif /* LOOKUP_TABLE_H */ 
