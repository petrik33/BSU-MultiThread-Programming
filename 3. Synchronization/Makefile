# Compiler settings
CC := g++
CFLAGS := -std=c++17 -Wall -Wextra -pedantic

# Directories
SRC_DIR := src
INCLUDE_DIR := includes
OBJ_DIR := obj
BIN_DIR := bin
TEST_DIR := test

# Source files
SRC := $(wildcard $(SRC_DIR)/*.cc)
TEST_SRC := $(wildcard $(TEST_DIR)/*.cc)

# Object files
OBJ := $(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRC))
TEST_OBJ := $(patsubst $(TEST_DIR)/%.cc,$(OBJ_DIR)/%.o,$(TEST_SRC))

# Libraries
LIBS := 
TEST_LIBS := -lgtest -lgtest_main

# Main target
MAIN_TARGET := $(BIN_DIR)/main
$(MAIN_TARGET): $(OBJ) $(OBJ_DIR)/main.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Debug target
DEBUG_TARGET := $(BIN_DIR)/debug
$(DEBUG_TARGET): $(OBJ) $(OBJ_DIR)/main.o | $(BIN_DIR)
	$(CC) $(CFLAGS) -g $^ -o $@ $(LIBS)

# Test target
TEST_TARGET := $(BIN_DIR)/test
$(TEST_TARGET): $(filter-out $(OBJ_DIR)/main.o,$(OBJ)) $(TEST_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(TEST_LIBS)

# Object files compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -g $< -o $@ -I$(INCLUDE_DIR)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cc | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -g $< -o $@ -I$(INCLUDE_DIR) -I$(TEST_DIR)

# Directories creation
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Phony targets
.PHONY: clean test run
build: $(MAIN_TARGET)
test: $(TEST_TARGET)
	$(TEST_TARGET)
run: build
	$(MAIN_TARGET)
debug: $(DEBUG_TARGET)
	gdb $(DEBUG_TARGET)
clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*
