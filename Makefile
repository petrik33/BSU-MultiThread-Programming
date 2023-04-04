# Compiler settings
CC := g++
CFLAGS := -std=c++17 -Wall -Wextra -pedantic

# Directories
SRC_DIR := src
INCLUDE_DIR := include
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
BOOST_LIBS := -lboost_chrono -lboost_thread

# Main target
MAIN_TARGET := $(BIN_DIR)/main
$(MAIN_TARGET): $(OBJ) $(OBJ_DIR)/main.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(BOOST_LIBS)

# Test target
TEST_TARGET := $(BIN_DIR)/test
$(TEST_TARGET): $(filter-out $(OBJ_DIR)/main.o,$(OBJ)) $(TEST_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(TEST_LIBS) $(BOOST_LIBS)

# Object files compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cc | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR) -I$(TEST_DIR)

# Directories creation
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Phony targets
.PHONY: clean test run
test: $(TEST_TARGET)
	$(TEST_TARGET)
run: $(MAIN_TARGET)
	$(MAIN_TARGET)
clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*