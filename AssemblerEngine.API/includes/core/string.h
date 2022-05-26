/*****************************************************************//**
 * @file   string.h
 * @ingroup group_api
 * @brief  
 * 
 * @author RickNijhuis
 * @date   May 2022
 *********************************************************************/

 /**
 *@addtogroup group_api
 * @{
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifndef AE_STRING_SIZE_TYPE
#define AE_STRING_SIZE_TYPE int32_t
#endif // AE_STRING_SIZE_TYPE

typedef char* string;

/// <summary>
/// creates an empty zero terminated string
/// </summary>
/// <returns>new zero terminated string</returns>
string string_create_empty();

/// <summary>
/// creates an empty zero terminated string
/// </summary>
/// <param name="str">: string to initialize with</param>
/// <returns>new string containing str param as value</returns>
string string_create(const char* str);

/// <summary>
/// concatinates two strings
/// </summary>
/// <param name="str1">: string to concatinate to</param>
/// <param name="str2">: string to concatinate</param>
/// <returns>string passed as str1 with concatinated value</returns>
string string_concat(string str1, string str2);

/// <summary>
/// copies given string to a new string
/// </summary>
/// <param name="str">: string to copy</param>
/// <returns>new string containing value of given string</returns>
string string_copy(string str);

/// <summary>
/// copies given string to specified string
/// </summary>
/// <param name="str">: string to copy</param>
/// <returns>string given as destination</returns>
string string_copy_to(string str, string dest);

/// <summary>
/// creates new string containing value between indices from given string
/// </summary>
/// <param name="str">: string to get the value from</param>
/// <param name="startIndex">: index to first character of substring</param>
/// <param name="endIndex">: index to last character of substring</param>
/// <returns>new string containing value of substring</returns>
string string_substring(string str, AE_STRING_SIZE_TYPE startIndex, AE_STRING_SIZE_TYPE endIndex);

/// <summary>
/// reallocates string to new size
/// </summary>
/// <param name="str">: string to resize</param>
/// <param name="size">: size to reallocate to</param>
/// <returns>reallocated string of given given size</returns>
string string_resize(string str, AE_STRING_SIZE_TYPE size);

/// <summary>
/// appends character to end of string if size is large enough
/// </summary>
/// <param name="str">: string to append to</param>
/// <param name="character">: character to append</param>
/// <returns>given string now with appended character or the given string if failed</returns>
string string_append(string str, const char character);

/// <summary>
/// checks whether string is null or empty
/// </summary>
/// <param name="str">: string to check</param>
/// <returns>true if string is null or empty, false otherwise</returns>
bool   string_is_null_or_empty(string str);

/// <summary>
/// frees given string, string must be created with one of the create functions
/// </summary>
/// <param name="str">: string to free</param>
void string_free(string str);

/// <summary>
/// sets length string to new lenght, can be used to overwrite buffer
/// </summary>
/// <param name="str">: string to set length</param>
/// <param name="size">: new length</param>
/// <returns>given string with new length</returns>
string string_set_length(string str, AE_STRING_SIZE_TYPE length);

/// <summary>
/// gets size of given string in constant time
/// </summary>
/// <param name="str">: string to get size from</param>
/// <returns>size of given string, returns 0 if string is NULL</returns>
AE_STRING_SIZE_TYPE string_get_size(string str);

/// <summary>
/// gets length(amount of characters) of given string in constant time
/// </summary>
/// <param name="str">: string to get length from</param>
/// <returns>length of given string, returns 0 if string is NULL</returns>
AE_STRING_SIZE_TYPE string_get_length(string str);

/**@}*/
