# Compiler and flags
CXX = g++
CXXFLAGS = -g -std=c++20 -I$(RAYLIB_PATH)
LDFLAGS = -L$(RAYLIB_PATH) -lraylib -lm -lmingw32 -lgdi32 -luser32 -lwinmm

# Raylib path
RAYLIB_PATH = C:\raylib\raylib\src

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Find all source files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
EXE = $(BIN_DIR)/game.exe

# Default target: Compile and Run
all: $(EXE)
	./$(EXE)  # On Windows, change to "$(EXE)" if using cmd or PowerShell

# Link the executable
$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure necessary directories exist
$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
