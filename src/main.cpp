#include "raylib.h"
#include "unit.hpp"
#include "skills.hpp"

const int GRID_SIZE = 25;
const int CELL_SIZE = 50;

std::vector<Unit> units; // Vector of units

void DrawGrid();

int main() {
    InitWindow(GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE, "Fire Emblem Roguelike Prototype");
    SetTargetFPS(60);
    
    // Creating units for demonstration
    units.emplace_back(50, 50, &units);
    units.back().setIsAlly(true); // Set as ally
    units.back().setColor(YELLOW); // Set color to yellow
    units.back().learnSkill(Skill("Fireball", fireball)); // Learn the slash skill
    units.back().learnSkill(Skill("Fuga", fireball)); // Set attack range to 2 for demonstration purposes
    units.back().setMoveRange(2); // Set move range

    units.emplace_back(100, 150, &units);
    units.back().setIsAlly(false); // Set as enemy

    while (!WindowShouldClose()) {
        // Handle inputs and update units
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Update and draw units
        for (auto& unit : units) {
            unit.update(); // Update the unit's state (e.g., selection, movement)
            unit.draw();   // Draw the unit
        }
        
        // Draw the grid
        DrawGrid();
        
        // Optionally highlight the selected unit (color change, etc.)
        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context
    return 0;
}

void DrawGrid() {
    // Draw the grid lines
    for (int i = 0; i <= GRID_SIZE; i++) {
        DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, GRID_SIZE * CELL_SIZE, BLACK);
        DrawLine(0, i * CELL_SIZE, GRID_SIZE * CELL_SIZE, i * CELL_SIZE, BLACK);
    }
}
