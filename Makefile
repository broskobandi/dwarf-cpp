PROJECT := dwarf
OS = linux
BUILD_TYPE = debug
COMPILE_COMMANDS := build/compile_commands.json
CC = bear --output build/compile_commands.json -- clang++
CFLAGS = -Wall -Wextra -Wunused-result -Wconversion
CPPFLAGS = -Isrc
LDFLAGS = -lSDL2

BUILD_DIR := build/$(OS)/$(BUILD_TYPE)
OBJ_DIR := $(BUILD_DIR)/obj
SRC_DIR := src

MAIN := $(SRC_DIR)/main.cpp
SRC := $(filter-out $(MAIN), $(wildcard $(SRC_DIR)/*.cpp))

OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
BIN := $(BUILD_DIR)/$(PROJECT)

.PHONY: all run clean distclean

all: $(BIN)

run: $(BIN)
	./$<

clean:
	rm -rf $(BIN) $(OBJ) $(COMPILE_COMMANDS)

distclean:
	rm -rf build

$(BIN): $(MAIN) $(OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp | $(OBJ_DIR)
	$(CC) -c -fPIC $(CFLAGS) $(CPPFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@
