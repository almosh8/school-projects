all: door_struct list_test stack_test

runall:
	./../build/Quest_1
	./../build/Quest_2
	./../build/Quest_3

door_struct:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra door_struct.h dmanager_module.c -o ../build/Quest_1
	@echo "build/Quest_1" >> ../.gitignore

list_test:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra door_struct.h list.c list_test.c -o ../build/Quest_2
	@echo "build/Quest_2" >> ../.gitignore

stack_test:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra stack.c stack_test.c -o ../build/Quest_3
	@echo "../build/Quest_3" >> ../.gitignore

clean:
	rm -rf ../build

rebuild: clean all

rb: rebuild runall
