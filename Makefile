# Code used from: https://stackoverflow.com/questions/30573481/path-include-and-src-directory-makefile/30602701

# Directories
PROJ_SRC_DIR 	:= src
PROJ_OBJ_DIR 	:= obj
PROJ_BIN_DIR	:= bin

TEST_SRC_DIR	:= tests/src
TEST_OBJ_DIR 	:= tests/obj
TEST_BIN_DIR 	:= tests/bin

# Executables
PROJ_EXEC		:= $(PROJ_BIN_DIR)/pipeSim
TEST_EXEC		:= $(TEST_BIN_DIR)/pipeSimTests

# Source / Object Files
PROJ_SRC		:= $(wildcard $(PROJ_SRC_DIR)/*.cpp) \
					$(wildcard $(PROJ_SRC_DIR)/instr/*.cpp) \
		   			$(wildcard $(PROJ_SRC_DIR)/memory/*.cpp)
PROJ_OBJ		:= $(PROJ_SRC:%.cpp=$(PROJ_OBJ_DIR)/%.o)

TEST_SRC		:= $(wildcard $(TEST_SRC_DIR)/*.cpp) \
					$(wildcard $(PROJ_SRC_DIR)/instr/*.cpp) \
					$(wildcard $(TEST_SRC_DIR)/instr/*.cpp) \
					$(wildcard $(PROJ_SRC_DIR)/memory/*.cpp) \
					$(wildcard $(TEST_SRC_DIR)/memory/*.cpp)
TEST_OBJ		:= $(TEST_SRC:%.cpp=$(TEST_OBJ_DIR)/%.o)

# Compiler / Linker Flags
PROJ_CFLAGS		:= -Iinclude/ -Wall -MMD -MP -std=c++11
PROJ_LDFLAGS	:=

TEST_CFLAGS		:= -I./ -Iinclude/ -Wall -MMD -MP -std=c++11 -DCATCH_CONFIG_FAST_COMPILE
TEST_LDFLAGS	:= 

# --
# Steps
# --
.PHONY: all test run clean

# -- Basic Methods
all: $(PROJ_EXEC)

run: all
	./$(PROJ_EXEC)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	$(RM) -rv $(PROJ_BIN_DIR) $(PROJ_OBJ_DIR) $(TEST_BIN_DIR) $(TEST_OBJ_DIR)

# -- Compilation Methods
$(PROJ_EXEC): $(PROJ_OBJ) | $(PROJ_BIN_DIR)
	$(CXX) $(PROJ_LDFLAGS) $^ -o $@

$(TEST_EXEC): $(TEST_OBJ) | $(TEST_BIN_DIR)
	$(CXX) $(TEST_LDFLAGS) $^ -o $@

$(PROJ_BIN_DIR):
	mkdir -p $@

$(TEST_BIN_DIR):
	mkdir -p $@

$(PROJ_OBJ_DIR)/%.o: %.cpp | $(PROJ_OBJ_DIR)
	mkdir -p '$(@D)'
	$(CXX) $(PROJ_CFLAGS) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: %.cpp | $(TEST_OBJ_DIR)
	mkdir -p '$(@D)'
	$(CXX) $(TEST_CFLAGS) -c $< -o $@

$(PROJ_OBJ_DIR):
	mkdir -p $@

$(TEST_OBJ_DIR):
	mkdir -p $@

# -- Dependency Generation
-include $(PROJ_OBJ:.o=.d)
-include $(TEST_OBJ:.o=.d)