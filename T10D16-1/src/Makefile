all: strlen_tests strcmp_test strcpy_test strcat_test strchr_tests strstr_tests strtok_tests text_processor

runall:
	./../build/Quest_1
	./../build/Quest_2
	./../build/Quest_3
	./../build/Quest_4
	./../build/Quest_5
	./../build/Quest_6
	./../build/Quest_7
	./../build/Quest_8 -w

strlen_tests:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra s21_string_test.c s21_string.c -o ../build/Quest_1 -DSTRLEN
	@echo "build/Quest_1" >> ../.gitignore

strcmp_test:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra s21_string_test.c s21_string.c -o ../build/Quest_2 -DSTRCMP
	@echo "build/Quest_2" >> ../.gitignore

strcpy_test:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra s21_string_test.c s21_string.c -o ../build/Quest_3 -DSTRCPY
	@echo "build/Quest_3" >> ../.gitignore

strcat_test:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra s21_string_test.c s21_string.c -o ../build/Quest_4 -DSTRCAT
	@echo "build/Quest_4" >> ../.gitignore

strchr_tests:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra s21_string_test.c s21_string.c -o ../build/Quest_5 -DSTRCHR
	@echo "build/Quest_5" >> ../.gitignore

strstr_tests:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra s21_string_test.c s21_string.c -o ../build/Quest_6 -DSTRSTR
	@echo "build/Quest_6" >> ../.gitignore

strtok_tests:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra s21_string_test.c s21_string.c -o ../build/Quest_7 -DSTRTOK
	@echo "build/Quest_7" >> ../.gitignore

text_processor:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra text_processor.c s21_string.c -o ../build/Quest_8
	@echo "build/Quest_8" >> ../.gitignore

clean:
	rm -rf ../build

rebuild: clean all

rb: clean all runall
