#include "unit.hpp"
#include <iostream>
#include <cmath>


constexpr int MOVE_STEP = 50;
constexpr int WIDTH = 40;  // Assuming default width
constexpr int HEIGHT = 40; // Assuming default height


int snapToGrid(int value) {
    return (value / MOVE_STEP) * MOVE_STEP;
}


Unit::Unit(int x, int y, std::vector<Unit>* units) : x(x), y(y), state(IDLE), moveRange(1), units(units) {
    stats.health = 100;   // Default health
    stats.attack = 20; // Default attack damage
    stats.defense = 10;  // Default defense
    stats.color = RED; // Default color for the unit, can be changed later
    stats.attackRange = 1; // Default attack range
}


void Unit::move(int dx, int dy) {
    x = snapToGrid(x + dx);
    y = snapToGrid(y + dy);
}


void Unit::update() {
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    static bool attacked = false;
    if(buffer)performAction(hoveredAction); // Reset action to NONE before checking for new input



    switch (state) {
        case IDLE:
            if (mouseX >= x && mouseX <= x + WIDTH &&
                mouseY >= y && mouseY <= y + HEIGHT &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                state = SELECTED;
                std::cout << "Unit selected at (" << x << ", " << y << ")\n";
            }
            break;
        case SELECTED:
            if (IsKeyPressed(KEY_TAB) &&
            mouseX >= x && mouseX <= x + WIDTH &&
            mouseY >= y && mouseY <= y + HEIGHT) {
            isMenuOpen = isMenuOpen? false : true;  // Toggle the menu open/closed
        }
            if(isMenuOpen)showMenu();  // Show the action menu

            if (isMenuOpen) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    performAction(hoveredAction);  // Perform the selected action
                    isMenuOpen = false;  // Close the menu
                } 
            }
            break;
    }
}


void Unit::showMenu() {
    int menuWidth = 150;
    int menuHeight = 140;
    int xPos = x + WIDTH + 10;  // Display the menu to the right of the unit
    int yPos = y;

    // Draw the background for the menu
    DrawRectangle(xPos, yPos, menuWidth, menuHeight, Color{0, 0, 0, 180});

    // Draw the menu options
    Color attackColor = hoveredAction == ATTACK ? Color{255, 0, 0, 255} : Color{200, 200, 200, 255};
    DrawText("Attack", xPos + 10, yPos + 10, 20, attackColor);

    Color skillsColor = hoveredAction == SKILLS ? Color{0, 255, 0, 255} : Color{200, 200, 200, 255};
    DrawText("Skills", xPos + 10, yPos + 40, 20, skillsColor);

    Color defendColor = hoveredAction == DEFEND ? Color{0, 0, 255, 255} : Color{200, 200, 200, 255};
    DrawText("Defend", xPos + 10, yPos + 70, 20, defendColor);

    Color moveColor = hoveredAction == MOVE ? Color{255, 255, 0, 255} : Color{200, 200, 200, 255}; // Optional: Add a move option if needed
    DrawText("Move", xPos + 10, yPos + 100, 20, moveColor);

    // Optionally, add logic to highlight the hovered action
    if (GetMouseX() >= xPos && GetMouseX() <= xPos + menuWidth) {
        if (GetMouseY() >= yPos + 10 && GetMouseY() <= yPos + 30) {
            hoveredAction = ATTACK;
        } else if (GetMouseY() >= yPos + 40 && GetMouseY() <= yPos + 60) {
            hoveredAction = SKILLS;
        } else if (GetMouseY() >= yPos + 70 && GetMouseY() <= yPos + 90) {
            hoveredAction = DEFEND;
        }
        else if (GetMouseY() >= yPos + 100 && GetMouseY() <= yPos + 120) {
            hoveredAction = MOVE; // Highlight move option
        } else {
            hoveredAction = NONE; // No action hovered
        }
    }
}

bool go = false; // Flag to indicate whether the user has clicked to select a move target

void Unit::performAction(Action action) {
    int skillOffsetY = 20;
    int menuWidth = 150;
    int menuHeight = 140;
    int xPos = x + WIDTH + 10;  // Display the menu to the right of the unit
    int yPos = y;
    switch (action) {
        case ATTACK:
            // Step 1: Highlight valid move options
            highlightAttackOptions(); // Highlight possible move options when the unit is selected
            buffer = true; // Set a flag to indicate that an action has been performed
            // Step 2: Wait for user input (click or keyboard press)
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && go) {  // Left-click to select move target
                int targetX = snapToGrid(GetMouseX());
                int targetY = snapToGrid(GetMouseY());
                // Check if the target position is valid
                attack(targetX, targetY); // Perform the attack on the target unit
                go = false; // Reset the flag to indicate that no action has been performed
                buffer = false; // Reset the buffer to indicate that the action has been completed
            }else if (IsKeyPressed(KEY_Q)) {  // Q key to cancel attack
                
                std::cout << "Attack cancelled.\n";
                buffer = false; // Reset the flag to indicate that no action has been performed
                state = IDLE;  // Return to idle state
                go = false; // Reset the flag to indicate that no action has been performed
                return; // Exit early to avoid further processing
            }else if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !go) { // Allow the first click to confirm the attack mode
                go = true; // Set the flag to true to allow attack selection
            }

            break;
        case SKILLS:
            // Handle skill selection and execution
            buffer = true; // Set a flag to indicate that an action has been performed
                DrawRectangle(xPos + 180, yPos, menuWidth * 4, menuHeight * 2, Color{0, 0, 0, 180});
                for (size_t i = 0; i < stats.skills.size(); ++i) {
                    Color skillColor = hoveredAction == SKILLS ? Color{200, 200, 255, 255} : Color{200, 200, 200, 255};
                    DrawText(stats.skills[i].name.c_str(), xPos + 200, yPos + skillOffsetY, 20, skillColor);
                    skillOffsetY += 30; // Increase vertical spacing
                }
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && go) {  // Left-click to select a skill
                    int skillStartY = yPos;  // Y position where skills start
                    int skillHeight = 30;    // Height per skill entry
                    int skillStartX = xPos + 200;  // X position where skill names are drawn
                    int skillEndX = skillStartX + menuWidth * 4;  // End X boundary
                
                    Vector2 mousePos = GetMousePosition();
                
                    for (size_t i = 0; i < stats.skills.size(); ++i) {
                        int skillY = skillStartY + (i * skillHeight);  // Calculate skill Y position
                
                        // Check if the mouse is within the skill's bounding box
                        if (mousePos.x >= skillStartX && mousePos.x <= skillEndX &&
                            mousePos.y >= skillY && mousePos.y <= skillY + skillHeight) {
                            
                            std::cout << "Using skill: " << stats.skills[i].name << std::endl;
                            stats.skills[i].effect(*this, units->back()); // This is placeholder (back()), False for preview (no preview logic yet)
                            buffer = false; // Reset buffer after action
                            go = false; // Action completed
                            break; // Stop after selecting a skill
                        }
                    }
                }else if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !go) { // Allow the first click to confirm the skill selection mode
                go = true; // Set the flag to true to allow skill selection
            }
            break;
        case DEFEND:
            std::cout << "Defend action selected.\n";
            // Implement defend logic here
            break;
        case MOVE:
            // Step 1: Highlight valid move options
            highlightMoveOptions(); // Highlight possible move options when the unit is selected
            buffer = true; // Set a flag to indicate that an action has been performed
            // Step 2: Wait for user input (click or keyboard press)
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && go) {  // Left-click to select move target
                int targetX = snapToGrid(GetMouseX());
                int targetY = snapToGrid(GetMouseY());

                // Check if the target position is valid
                if (isValidMove(targetX, targetY)) {
                    // Confirm the move
                    move(targetX - x, targetY - y); // Move the unit to the selected position
                    std::cout << "Moved to (" << targetX << ", " << targetY << ")\n";
                    state = IDLE; // Return to idle state after moving
                } else {
                    std::cout << "Invalid move to (" << targetX << ", " << targetY << ")\n";
                }
                buffer = false; // Reset the flag to indicate that no action has been performed
                go = false; // Reset the flag to indicate that no action has been performed
            }

            // Optional: Allow canceling move selection (press ESC to cancel move)
            if (IsKeyPressed(KEY_Q)) {
                std::cout << "Move cancelled.\n";
                buffer = false; // Reset the flag to indicate that no action has been performed
                state = IDLE;  // Return to idle state
                go = false; // Reset the flag to indicate that no action has been performed
            }else if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !go) { // Allow the first click to confirm the move mode
                go = true; // Set the flag to true to allow move selection
            }

            break;
        default:
            break;
    }
}



void Unit::draw() const {
    DrawRectangle(x, y, WIDTH, HEIGHT, stats.color); // Draw the unit's rectangle
    if(GetMouseX() >= x && GetMouseX() <= x + WIDTH &&
        GetMouseY() >= y && GetMouseY() <= y + HEIGHT){
            DrawRectangle(x, y, WIDTH, HEIGHT, Color{255,255,255,100}); // Highlight the unit when mouse is over it
        }
}


bool Unit::isCollision(const Unit& other) const {
    return (x < other.x + WIDTH && x + WIDTH > other.x) &&
           (y < other.y + HEIGHT && y + HEIGHT > other.y);
}


void Unit::highlightMoveOptions() const {
    for (int i = 1; i <= moveRange; ++i) {
        for (int j = 1; j <= moveRange; ++j) {
            // Fill horizontal squares (left-right)
            DrawRectangle(x + MOVE_STEP * i, y + MOVE_STEP * j, WIDTH, HEIGHT, Color{200, 200, 200, 100});  // Right-Down
            DrawRectangle(x - MOVE_STEP * i, y + MOVE_STEP * j, WIDTH, HEIGHT, Color{200, 200, 200, 100});  // Left-Down
            DrawRectangle(x + MOVE_STEP * i, y - MOVE_STEP * j, WIDTH, HEIGHT, Color{200, 200, 200, 100});  // Right-Up
            DrawRectangle(x - MOVE_STEP * i, y - MOVE_STEP * j, WIDTH, HEIGHT, Color{200, 200, 200, 100});  // Left-Up
           
            // Fill vertical squares (up-down)
            DrawRectangle(x + MOVE_STEP * i, y, WIDTH, HEIGHT, Color{200, 200, 200, 100});  // Right
            DrawRectangle(x - MOVE_STEP * i, y, WIDTH, HEIGHT, Color{200, 200, 200, 100});  // Left
            DrawRectangle(x, y + MOVE_STEP * j, WIDTH, HEIGHT, Color{200, 200, 200, 100});  // Down
            DrawRectangle(x, y - MOVE_STEP * j, WIDTH, HEIGHT, Color{200, 200, 200, 100});  // Up
        }
    }
}


void Unit::highlightAttackOptions() const {
    int attackRange = getAttackRange(); // Use the unit's attack range (different from moveRange)
    for (int i = 1; i <= attackRange; ++i) {
        for (int j = 1; j <= attackRange; ++j) {
            // Highlight in a different color for attack
            DrawRectangle(x + MOVE_STEP * i, y + MOVE_STEP * j, WIDTH, HEIGHT, Color{200, 0, 0, 100});  // Right-Down
            DrawRectangle(x - MOVE_STEP * i, y + MOVE_STEP * j, WIDTH, HEIGHT, Color{200, 0, 0, 100});  // Left-Down
            DrawRectangle(x + MOVE_STEP * i, y - MOVE_STEP * j, WIDTH, HEIGHT, Color{200, 0, 0, 100});  // Right-Up
            DrawRectangle(x - MOVE_STEP * i, y - MOVE_STEP * j, WIDTH, HEIGHT, Color{200, 0, 0, 100});  // Left-Up
            DrawRectangle(x + MOVE_STEP * i, y, WIDTH, HEIGHT, Color{200, 0, 0, 100});  // Right
            DrawRectangle(x - MOVE_STEP * i, y, WIDTH, HEIGHT, Color{200, 0, 0, 100});  // Left
            DrawRectangle(x, y + MOVE_STEP * j, WIDTH, HEIGHT, Color{200, 0, 0, 100});  // Down
            DrawRectangle(x, y - MOVE_STEP * j, WIDTH, HEIGHT, Color{200, 0, 0, 100});  // Up
        }
    }
}


bool Unit::isValidMove(int targetX, int targetY) const {
    targetX = snapToGrid(targetX);
    targetY = snapToGrid(targetY);

    // Check if the target is within the unit's move range (manhattan distance or diagonal)
    int dx = abs(targetX - x);
    int dy = abs(targetY - y);
    if (dx <= MOVE_STEP * moveRange && dy <= MOVE_STEP * moveRange) {
        // Check for collision with other units in the target position
        for (auto& other : *units) {
            if (&other == this) continue;  // Skip self to avoid self-collision check

            if (other.getX() == targetX && other.getY() == targetY) {
                std::cout << "Target position (" << targetX << ", " << targetY << ") is occupied by another unit.\n";
                return false; // Can't move to a position occupied by another unit
            }
        }
        return true;
    }
    return false;
}


int Unit::getX() const { return x; }
int Unit::getY() const { return y; }




void Unit::attack(int targetX, int targetY) {
    // Calculate the distance between this unit and the target position
    int dx = abs(targetX - x);
    int dy = abs(targetY - y);

    // Check if the target is within the attack range (Manhattan distance for simplicity)
    if (dx <= MOVE_STEP * stats.attackRange && dy <= MOVE_STEP * stats.attackRange) {

        // Check for collision with other units at the target position
        for (auto& other : *units) {
            if (&other == this) continue;  // Skip self

            // Check if the target position matches another unit's position
            if (other.getX() == targetX && other.getY() == targetY) {

                // Check if the unit is an enemy (assuming getIsAlly() returns true for allies)
                if (!other.getIsAlly()) {
                    std::cout << "Attacking enemy at (" << other.getX() << ", " << other.getY() << ")\n";
                    other.takeDamage(stats.attack);  // Perform the attack and reduce health
                } else {
                    std::cout << "Cannot attack ally at (" << other.getX() << ", " << other.getY() << ")\n";
                }
                break; // Target found and attacked, exit the loop
            }
        }
    } else {
        std::cout << "Target is out of range for the attack.\n";
    }
}

