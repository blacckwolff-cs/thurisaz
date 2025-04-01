# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

# Raylib paths (Update if needed)
RAYLIB_DIR := C:/raylib
INCLUDE := -I$(RAYLIB_DIR)/include
LIBS := -L$(RAYLIB_DIR)/lib -lraylib -lopengl32 -lgdi32 -lwinmm -Wl,-subsystem,console

# Directories
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := bin/obj

# Source and object files
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# Output executable
TARGET := $(BIN_DIR)/roguelike.exe

# Build rules
all: setup $(TARGET)

setup:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Clean compiled files
clean:
	@del /Q /F $(OBJ) 2>nul || echo "No object files to delete."
	@del /Q /F $(TARGET) 2>nul || echo "No executable to delete."

# Run the game
run: all
	./$(TARGET)
