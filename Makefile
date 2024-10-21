# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Isrc -Isrc/parsing  
LDFLAGS =

# Directories and files
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/parsing/*.c)  
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# The output executable
TARGET = $(BIN_DIR)/quash

# Default rule
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES) $(LDFLAGS)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/parsing/%.o: $(SRC_DIR)/parsing/%.c  # Fixed pattern for parsing files
	@mkdir -p $(OBJ_DIR)/parsing  # Ensure parsing directory exists
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Test the executable
test: $(TARGET)
	./$(TARGET)

# Generate documentation
doc:
	doxygen Doxyfile

.PHONY: all clean test doc
