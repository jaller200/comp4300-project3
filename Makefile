# Code used from: https://stackoverflow.com/questions/30573481/path-include-and-src-directory-makefile/30602701

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Executables
EXEC	:= $(BIN_DIR)/pipeSim

# Source / Object Files
SRC		:= $(wildcard src/*.cpp)
OBJ		:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

# Compiler / Linker Flags
CFLAGS	:= -Iinclude -Wall -MMD -MP -std=c++11
LDFLAGS	:=

# --
# Steps
# --
.PHONY: all clean run

# -- Basic Methods
all: $(EXEC)

run: all
	./$(EXEC)

clean:
	$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

# -- Compilation Methods
$(EXEC): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	mkdir -p '$(@D)'
	$(CXX) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

# -- Dependency Generation
-include $(OBJ:.o=.d)