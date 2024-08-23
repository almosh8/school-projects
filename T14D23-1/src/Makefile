all: state_sort state_search clear_state

runall:
	./../build/Quest_1
	./../build/Quest_2
	./../build/Quest_3

state_sort: state_sort.c
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra state_sort.c -o ../build/Quest_1
	@echo "build/Quest_1" >> ../.gitignore

state_search: state_search.c
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra state_search.c -o ../build/Quest_2
	@echo "build/Quest_2" >> ../.gitignore

clear_state: clear_state.c
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra clear_state.c -o ../build/Quest_3
	@echo "build/Quest_3" >> ../.gitignore




clean:
	rm -rf ../build

rebuild: clean all

rb: clean all runall
