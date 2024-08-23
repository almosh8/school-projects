#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

int s21_strlen(const char *str);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, int n);
char *s21_strcpy(char *to, const char *from);
char *s21_strcat(char *dest, const char *src);
char *s21_strchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

#endif  // SRC_S21_STRING_H_
