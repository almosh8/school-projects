all: print_module documentation_module bst_create_test bst_insert_test bst_traverse_test

runall:
	./../build/Quest_1
	./../build/Quest_2
	./../build/Quest_3
	./../build/Quest_4
	./../build/Quest_5

print_module:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra print_module.c main_module_entry_point.c -o ../build/Quest_1
	@echo "build/Quest_1" >> ../.gitignore

documentation_module:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra documentation_module.c main_module_entry_point.c -o ../build/Quest_2 -DDOC
	@echo "build/Quest_2" >> ../.gitignore

bst_create_test:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra bst.c bst_create_test.c -o ../build/Quest_3
	@echo "build/Quest_3" >> ../.gitignore

bst_insert_test:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra bst.c bst_insert_test.c -o ../build/Quest_4
	@echo "build/Quest_4" >> ../.gitignore

bst_traverse_test:
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra bst.c bst_traverse_test.c -o ../build/Quest_5
	@echo "build/Quest_5" >> ../.gitignore



clean:
	rm -rf ../build

rebuild: clean all

rb: clean all runall
