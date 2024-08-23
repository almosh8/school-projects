#include "s21_string.h"

#include <stdio.h>

#ifdef STRLEN
#define TEST s21_strlen_test
#elif STRCMP
#define TEST s21_strcmp_test
#elif STRCPY
#define TEST s21_strcpy_test
#elif STRCAT
#define TEST s21_strcat_test
#elif STRSTR
#define TEST s21_strstr_test
#elif STRTOK
#define TEST s21_strtok_test
#elif STRCHR
#define TEST s21_strchr_test
#else
#define TEST s21_strlen_test /* DEFAULT */
#endif

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
void s21_strcat_test();
void s21_strstr_test();
void s21_strtok_test();
void s21_strchr_test();

int main() {
    TEST();
    return 0;
}

void s21_strlen_test() {
    // Normal value test
    char normal[] = "Hello, World!";
    printf("Input: %s, Output: %d, Test result: %s\n", normal, s21_strlen(normal),
           s21_strlen(normal) == 13 ? "SUCCESS" : "FAIL");

    // Abnormal value test
    char abnormal[] = "";
    printf("Input: %s, Output: %d, Test result: %s\n", abnormal, s21_strlen(abnormal),
           s21_strlen(abnormal) == 0 ? "SUCCESS" : "FAIL");

    // Boundary value test
    char boundary[] = "a";
    printf("Input: %s, Output: %d, Test result: %s\n", boundary, s21_strlen(boundary),
           s21_strlen(boundary) == 1 ? "SUCCESS" : "FAIL");
}

void s21_strcmp_test() {
    // Normal value test
    char normal1[] = "Hello";
    char normal2[] = "Hello";
    printf("Input: %s, %s, Output: %d, Test result: %s\n", normal1, normal2, s21_strcmp(normal1, normal2),
           s21_strcmp(normal1, normal2) == 0 ? "SUCCESS" : "FAIL");

    // Abnormal value test
    char abnormal1[] = "";
    char abnormal2[] = "Hello";
    printf("Input: %s, %s, Output: %d, Test result: %s\n", abnormal1, abnormal2,
           s21_strcmp(abnormal1, abnormal2), s21_strcmp(abnormal1, abnormal2) < 0 ? "SUCCESS" : "FAIL");

    // Boundary value test
    char boundary1[] = "a";
    char boundary2[] = "b";
    printf("Input: %s, %s, Output: %d, Test result: %s\n", boundary1, boundary2,
           s21_strcmp(boundary1, boundary2), s21_strcmp(boundary1, boundary2) < 0 ? "SUCCESS" : "FAIL");
}

void s21_strcpy_test() {
    // Normal value test
    char normal_from[] = "Hello, World!";
    char normal_to[100] = {0};
    s21_strcpy(normal_to, normal_from);
    printf("Input: %s, Output: %s, Test result: %s\n", normal_from, normal_to,
           s21_strcmp(normal_to, normal_from) == 0 ? "SUCCESS" : "FAIL");

    // Abnormal value test
    char abnormal_from[] = "";
    char abnormal_to[100] = {0};
    s21_strcpy(abnormal_to, abnormal_from);
    printf("Input: %s, Output: %s, Test result: %s\n", abnormal_from, abnormal_to,
           s21_strcmp(abnormal_to, abnormal_from) == 0 ? "SUCCESS" : "FAIL");

    // Boundary value test
    char boundary_from[] = "a";
    char boundary_to[100] = {0};
    s21_strcpy(boundary_to, boundary_from);
    printf("Input: %s, Output: %s, Test result: %s\n", boundary_from, boundary_to,
           s21_strcmp(boundary_to, boundary_from) == 0 ? "SUCCESS" : "FAIL");
}

void s21_strcat_test() {
    // Normal value test
    char normal_dest[] = "Hello, ";
    char normal_src[] = "World!";
    char normal_result[100] = {0};
    s21_strcpy(normal_result, normal_dest);
    s21_strcat(normal_result, normal_src);
    printf("Input: %s, %s, Output: %s, Test result: %s\n", normal_dest, normal_src, normal_result,
           s21_strcmp(normal_result, "Hello, World!") == 0 ? "SUCCESS" : "FAIL");

    // Abnormal value test
    char abnormal_dest[] = "";
    char abnormal_src[] = "World!";
    char abnormal_result[100] = {0};
    s21_strcpy(abnormal_result, abnormal_dest);
    s21_strcat(abnormal_result, abnormal_src);
    printf("Input: %s, %s, Output: %s, Test result: %s\n", abnormal_dest, abnormal_src, abnormal_result,
           s21_strcmp(abnormal_result, "World!") == 0 ? "SUCCESS" : "FAIL");

    // Boundary value test
    char boundary_dest[] = "a";
    char boundary_src[] = "b";
    char boundary_result[100] = {0};
    s21_strcpy(boundary_result, boundary_dest);
    s21_strcat(boundary_result, boundary_src);
    printf("Input: %s, %s, Output: %s, Test result: %s\n", boundary_dest, boundary_src, boundary_result,
           s21_strcmp(boundary_result, "ab") == 0 ? "SUCCESS" : "FAIL");
}

void s21_strchr_test() {
    // Normal value test
    char normal_str[] = "Hello, World!";
    char normal_char = 'o';
    char *normal_result = s21_strchr(normal_str, normal_char);
    printf("Input: %s, %c, Output: %s, Test result: %s\n", normal_str, normal_char,
           normal_result != NULL ? normal_result : "NULL",
           normal_result != NULL && s21_strcmp(normal_result, "o, World!") == 0 ? "SUCCESS" : "FAIL");

    // Abnormal value test
    char abnormal_str[] = "Hello, World!";
    char abnormal_char = 'x';
    char *abnormal_result = s21_strchr(abnormal_str, abnormal_char);
    printf("Input: %s, %c, Output: %s, Test result: %s\n", abnormal_str, abnormal_char,
           abnormal_result == NULL ? "NULL" : abnormal_result, abnormal_result == NULL ? "SUCCESS" : "FAIL");

    // Boundary value test
    char boundary_str[] = "a";
    char boundary_char = 'a';
    char *boundary_result = s21_strchr(boundary_str, boundary_char);
    printf("Input: %s, %c, Output: %s, Test result: %s\n", boundary_str, boundary_char,
           boundary_result != NULL ? boundary_result : "NULL",
           boundary_result != NULL && s21_strcmp(boundary_result, "a") == 0 ? "SUCCESS" : "FAIL");
}

void s21_strstr_test() {
    // Normal value test
    char normal_haystack[] = "Hello, World!";
    char normal_needle[] = "World";
    char *normal_result = s21_strstr(normal_haystack, normal_needle);
    printf("Input: %s, %s, Output: %s, Test result: %s\n", normal_haystack, normal_needle, normal_result,
           normal_result != NULL && s21_strcmp(normal_result, "World!") == 0 ? "SUCCESS" : "FAIL");

    // Abnormal value test
    char abnormal_haystack[] = "Hello, World!";
    char abnormal_needle[] = "";
    char *abnormal_result = s21_strstr(abnormal_haystack, abnormal_needle);
    printf("Input: %s, %s, Output: %s, Test result: %s\n", abnormal_haystack, abnormal_needle,
           abnormal_result,
           abnormal_result != NULL && s21_strcmp(abnormal_result, "Hello, World!") == 0 ? "SUCCESS" : "FAIL");

    // Boundary value test
    char boundary_haystack[] = "a";
    char boundary_needle[] = "a";
    char *boundary_result = s21_strstr(boundary_haystack, boundary_needle);
    printf("Input: %s, %s, Output: %s, Test result: %s\n", boundary_haystack, boundary_needle,
           boundary_result,
           boundary_result != NULL && s21_strcmp(boundary_result, "a") == 0 ? "SUCCESS" : "FAIL");
}

void s21_strtok_test() {
    // Normal value test
    char normal_str[] = "Hello, World! How are you?";
    char buf[100] = {0};
    s21_strcpy(buf, normal_str);
    char normal_delim[] = " ,";
    char *normal_result = s21_strtok(buf, normal_delim);
    printf("Input: %s, %s, Output: %s, Test result: %s\n", normal_str, normal_delim, normal_result,
           normal_result != NULL && s21_strcmp(normal_result, "Hello") == 0 ? "SUCCESS" : "FAIL");
    normal_result = s21_strtok(NULL, normal_delim);
    while (normal_result != NULL) {
        printf("Output: %s, Test result: %s\n", normal_result,
               normal_result != NULL && s21_strcmp(normal_result, "World!") == 0 ? "SUCCESS"
               : normal_result != NULL && s21_strcmp(normal_result, "How") == 0  ? "SUCCESS"
               : normal_result != NULL && s21_strcmp(normal_result, "are") == 0  ? "SUCCESS"
               : normal_result != NULL && s21_strcmp(normal_result, "you?") == 0 ? "SUCCESS"
                                                                                 : "FAIL");
        normal_result = s21_strtok(NULL, normal_delim);
    }

    // Abnormal value test
    char abnormal_str[] = "";
    char abnormal_delim[] = " ,";
    char *abnormal_result = s21_strtok(abnormal_str, abnormal_delim);
    printf("Input: %s, %s, Output: %s, Test result: %s\n", abnormal_str, abnormal_delim,
           abnormal_result == NULL ? "NULL" : abnormal_result, abnormal_result == NULL ? "SUCCESS" : "FAIL");

    // Boundary value test
    char boundary_str[] = "a";
    char boundary_delim[] = "a";
    char *boundary_result = s21_strtok(boundary_str, boundary_delim);
    printf("Input: %s, %s, Output: %s, Test result: %s\n", boundary_str, boundary_delim,
           boundary_result == NULL ? "NULL" : boundary_result, boundary_result == NULL ? "SUCCESS" : "FAIL");
}