# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source and Object Files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Output binary name
TARGET = $(BIN_DIR)/program

# Rule for building the target
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule for building object files (now only depending on .cpp files)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: clean
