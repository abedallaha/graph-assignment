# Email: abedallahamodi803@gmail.com
# Makefile for Graph Implementation

CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
TESTFLAGS = -std=c++17 -Wall -Wextra -I./include

# Directories
SRC_DIR = src
TEST_DIR = test
OBJ_DIR = obj

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Test files
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Main executable
EXECUTABLE = graph_program
TEST_EXE = test_executable

# Library object files (excluding main.cpp)
LIB_SRCS = $(filter-out $(SRC_DIR)/main.cpp, $(SRCS))
LIB_OBJS = $(LIB_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(EXECUTABLE) $(TEST_EXE)

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Main executable
$(EXECUTABLE): $(OBJS) | $(OBJ_DIR)
	$(CXX) $(OBJS) -o $@
	chmod +x $@

# Test executable
$(TEST_EXE): $(TEST_OBJS) $(LIB_OBJS) | $(OBJ_DIR)
	$(CXX) $(TEST_OBJS) $(LIB_OBJS) -o $@
	chmod +x $@

# Object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(TESTFLAGS) -c $< -o $@

# Run targets
main: $(EXECUTABLE)
	./$(EXECUTABLE)

test: $(TEST_EXE)
	./$(TEST_EXE)

valgrind: $(EXECUTABLE)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXECUTABLE)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE) $(TEST_EXE)

.PHONY: all main test valgrind clean 