BUILD_DIR = ../build
BINARY = cipher
BINARY_LOG = logging_cipher

all: cipher logging_cipher

cipher: cipher.c
	@mkdir -p $(BUILD_DIR)
	gcc -Wall -Werror -Wextra cipher.c -o $(BUILD_DIR)/$(BINARY)
	@echo "$(BUILD_DIR)/$(BINARY)" >> ../.gitignore

logging_cipher: cipher.c
	@mkdir -p $(BUILD_DIR)
	gcc -Wall -Werror -Wextra cipher.c logger.c -o $(BUILD_DIR)/$(BINARY_LOG) -DLOG
	@echo "$(BUILD_DIR)/$(BINARY_LOG)" >> ../.gitignore

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

runall: $(BUILD_DIR)/$(BINARY_LOG)
	./$<

rb: rebuild runall