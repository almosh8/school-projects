SRC_DIR = ..
BUILD_DIR = $(SRC_DIR)/../build
MAIN_DIR = $(SRC_DIR)/main_executable_module
DATA_LIBS_DIR = $(SRC_DIR)/data_libs
DATA_MODULE_DIR = $(SRC_DIR)/data_module
DECISION_MODULE_DIR = $(SRC_DIR)/yet_another_decision_module

CC = gcc
CFLAGS = -Wall -Wextra -Werror -lm
MACROFLAG = -DMACRO
DYNAMICFLAG = -DDYNAMIC

MAIN_SRC = $(MAIN_DIR)/main_executable_module.c
DATA_IO_SRC = $(DATA_LIBS_DIR)/data_io.c
DATA_IO_MACRO_H = $(DATA_LIBS_DIR)/data_io_macro.h
DATA_STAT_SRC = $(DATA_LIBS_DIR)/data_stat.c
DATA_MODULE_SRC = $(DATA_MODULE_DIR)/data_process.c
DECISION_MODULE_SRC = $(DECISION_MODULE_DIR)/decision.c
DATA_SORT_SRC = $(MAIN_DIR)/data_sort.c

DATA_STAT_OBJ = $(DATA_STAT_SRC:.c=.o)
DATA_STAT_A = $(BUILD_DIR)/data_stat.a
DATA_PROCESS_OBJ = $(DATA_PROCESS_SRC:.c=.o)
DATA_PROCESS_SO = $(BUILD_DIR)/data_process.so

EXECUTABLE = $(BUILD_DIR)/Quest_3
MACRO = $(BUILD_DIR)/Quest_4
EXECUTABLE_STATIC = $(BUILD_DIR)/Quest_5
EXECUTABLE_DYNAMIC = $(BUILD_DIR)/Quest_6

all:
	$(MAKE) build
	$(MAKE) build_with_macro
	$(MAKE) data_stat.a
	$(MAKE) build_with_static
	$(MAKE) data_process.so
	$(MAKE) build_with_dynamic

build: $(MAIN_SRC) $(DATA_IO_SRC) $(DATA_MODULE_SRC) $(DECISION_MODULE_SRC) $(DATA_SORT_SRC) $(DATA_STAT_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) -o $(EXECUTABLE) $^ $(CFLAGS)
	@echo "$(EXECUTABLE)" >> ../../.gitignore

build_with_macro: $(MAIN_SRC) $(DATA_IO_MACRO_H) $(DATA_MODULE_SRC) $(DECISION_MODULE_SRC) $(DATA_SORT_SRC) $(DATA_STAT_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) -o $(MACRO) $^ $(CFLAGS) $(MACROFLAG)
	@echo "$(MACRO)" >> ../../.gitignore

data_stat.a: $(DATA_STAT_OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $^ $(DATA_STAT_SRC)
	ar rcs $(DATA_STAT_A) $^
	@echo "$(DATA_STAT_A)" >> ../.gitignore 

build_with_static: $(MAIN_SRC) $(DATA_IO_SRC) $(DATA_MODULE_SRC) $(DECISION_MODULE_SRC) $(DATA_SORT_SRC) $(BUILD_DIR)/data_stat.a
	@mkdir -p $(BUILD_DIR)
	$(CC) -o $(EXECUTABLE_STATIC) $^ -L :$(BUILD_DIR)/data_stat.a $(CFLAGS)
	@echo "$(EXECUTABLE_STATIC)" >> ../.gitignore

data_process.so: $(DATA_PROCESS_OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) -shared -o $(DATA_PROCESS_SO) $(DATA_PROCESS_OBJ) $(CFLAGS)
	@echo "$(DATA_PROCESS_SO)" >> ../../.gitignore

build_with_dynamic: $(MAIN_SRC) $(DATA_IO_SRC) $(DATA_MODULE_SRC) $(DECISION_MODULE_SRC) $(DATA_SORT_SRC) $(DATA_STAT_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) -o $(EXECUTABLE_DYNAMIC) $^ -L:$(DATA_PROCESS_SO) $(CFLAGS) $(DYNAMICFLAG)
	@echo "$(EXECUTABLE_DYNAMIC)" >> ../../.gitignore

clean:
	rm -rf $(BUILD_DIR)

rebuild:
	$(MAKE) clean
	$(MAKE) all
