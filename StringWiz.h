#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

/*
 * StringWiz: A versatile string utility library offering a comprehensive set of string manipulation functions.
 * 
 * StringWiz is designed to provide developers with a wide range of string-related tools, from basic operations 
 * like concatenation and substring extraction to more advanced features such as case-insensitive comparison 
 * and formatted string creation. 
 * source https://github.com/SharonIV0x86/StringWiz/
 */

/* Function to allocate memory for a new string */
char* str_malloc(int size) {
    return (char*)malloc(size * sizeof(char));
}

/* Function to free memory allocated for a string */
void str_free(char* str) {
    free(str);
}

/* 
 * Function to concatenate two strings 
 * 
 * @param destination Pointer to original String contains the concatanated string.
 * @param source Pointer to other string to be concatanated */
char* str_concat(const char* destination, const char* source) {
    char* result = (char*)malloc((strlen(destination) + strlen(source) + 1) * sizeof(char));
    strcpy(result, destination);
    strcat(result, source);
    return result;
}

/*
 * Function to create a substring from a string
 *
 * @param str Pointer to the original string.
 * @param start Starting index of the substring.
 * @param length Length of the substring.
 * @return A pointer to the substring.
 */
char* str_substr(const char* str, int start, int length) {
    
    char* result = (char*)malloc((length + 1) * sizeof(char));
    strncpy(result, str + start, length);
    result[length] = '\0';
    return result;
}

/* Function to replace occurrences of a substring in a string */
char* str_replace(const char* str, const char* old_sub, const char* new_sub) {
    char* result;
    char* ins;
    char* tmp;
    int len_old = strlen(old_sub);
    int len_new = strlen(new_sub);
    int len_str = strlen(str);
    int count = 0;
    const char* p;

    for (p = strstr(str, old_sub); p != NULL; p = strstr(p + len_old, old_sub)) {
        count++;
    }

    result = (char*)malloc(len_str + count * (len_new - len_old) + 1);

    if (result == NULL) {
        return NULL;
    }

    ins = result;
    for (p = str; (tmp = strstr(p, old_sub)) != NULL; p = tmp + len_old) {
        strncpy(ins, p, tmp - p);
        ins += tmp - p;
        strncpy(ins, new_sub, len_new);
        ins += len_new;
    }
    strcpy(ins, p);
    return result;
}

/* Function to convert a string to uppercase */
void str_to_upper(char* str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

/* Function to convert a string to lowercase */
void str_to_lower(char* str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}

/* Function to perform case-insensitive string comparison */
int str_cmp_ignore_case(const char* str1, const char* str2) {
    while (*str1 && *str2 && tolower(*str1) == tolower(*str2)) {
        str1++;
        str2++;
    }
    return tolower(*str1) - tolower(*str2);
}

/* Function to find the first occurrence of a substring in a string */
int str_find(const char* str, const char* sub) {
    char* ptr = strstr(str, sub);
    if (ptr == NULL) {
        return -1;
    }
    return ptr - str;
}

/* Function to find the last occurrence of a substring in a string */
int str_rfind(const char* str, const char* sub) {
    char* ptr = strstr(str, sub);
    char* last_ptr = NULL;
    while (ptr != NULL) {
        last_ptr = ptr;
        ptr = strstr(ptr + 1, sub);
    }
    if (last_ptr == NULL) {
        return -1;
    }
    return last_ptr - str;
}

/* Function to convert a string to an integer */
int str_to_int(const char* str) {
    return atoi(str);
}

/* Function to convert a string to a float */
float str_to_float(const char* str) {
    return atof(str);
}

/* Function to convert an integer to a string */
char* int_to_str(int num) {
    char* str = (char*)malloc(12 * sizeof(char)); // Maximum length of an integer string is 11 characters + 1 for null terminator
    sprintf(str, "%d", num);
    return str;
}

/* Function to convert a float to a string */
char* float_to_str(float num) {
    char* str = (char*)malloc(32 * sizeof(char)); // Maximum length of a float string is 31 characters + 1 for null terminator
    sprintf(str, "%f", num);
    return str;
}

/* Function to reverse a string */
void str_reverse(char* str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

/* Function to trim whitespace characters from the beginning and end of a string */
void str_trimWHS(char* str) {
    int length = strlen(str);
    int start = 0;
    int end = length - 1;
    while (isspace(str[start])) {
        start++;
    }
    while (end > start && isspace(str[end])) {
        end--;
    }
    str[end + 1] = '\0';
    memmove(str, str + start, end - start + 2);
}

/* Function to format a string */
char* str_format(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int len = vsnprintf(NULL, 0, format, args);
    va_end(args);
    
    char* str = (char*)malloc((len + 1) * sizeof(char));
    va_start(args, format);
    vsnprintf(str, len + 1, format, args);
    va_end(args);
    
    return str;
}