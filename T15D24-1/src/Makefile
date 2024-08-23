all: build_db

runall:
	./../build/Quest_1

build_db: modules_db.c
	@mkdir -p ../build
	gcc -Wall -Werror -Wextra modules_db.c shared.c modules.c levels.c status_events.c -o ../build/Quest_1
	@echo "build/Quest_1" >> ../.gitignore




clean:
	rm -rf ../build

rebuild: clean all

rb: clean all runall
