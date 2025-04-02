#ifndef UNIT_HPP
#define UNIT_HPP

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <functional> // For std::function


#include <raylib.h>

enum STATE{
    IDLE,
    MOVING,
    SELECTED
};

class Unit;

class Skill{
    // Add necessary attributes and methods for skills
    public:
    Skill(std::string name, std::function<void(Unit&, Unit&)> effect) : name(name), effect(effect) {}
    bool operator==(const Skill& other){
        return(this->name == other.name);
    }
    std::string name;
    std::string description;
    std::function<void(Unit&, Unit&)> effect; // Function to apply the skill's effect, e.g., damage calculation or healing

};

struct Stats{
    int health, attack, defense;
    std::vector<Skill> skills;
    int moveRange;
    Color color;
    int attackRange;
};

enum Action { NONE, ATTACK, SKILLS, DEFEND, MOVE };


class Unit{
    public:
        Unit(int x, int y, std::vector<Unit>* units);
        bool operator==(const Unit& other) const { // For std::remove to work correctly
            return (this == &other);
        }
        bool operator==(const Unit* other) const { 
            return (this == other);   
        }
        void showMenu();  // Display the action menu
        void performAction(Action action);  // Perform the action selected
        void move(int dx, int dy);
        int getX() const;
        int getY() const;
        void draw() const;
        bool isCollision(const Unit& other) const;
        void update(); // Placeholder for future logic, e.g. AI or state updates
        bool isValidMove(int dx, int dy) const; // Check if the unit can move to the specified position
        void highlightMoveOptions() const; // Highlight possible move options for the unit
        void highlightAttackOptions() const; // Highlight possible move options for the unit
        static const int WIDTH = 50;
        static const int HEIGHT = 50;
        int getAttackRange() const{return stats.attackRange;}; // Get the maximum distance the unit can attack
        void setAttackRange(int range){stats.attackRange = range;}; // Set the maximum distance the unit can attack
        int getMoveRange() const{return moveRange;}; // Get the maximum distance the unit can move
        void setMoveRange(int range){moveRange = range;}; // Set the maximum distance the unit can move
        bool getIsAlly() const{return isAlly;}; // Check if the unit is an ally
        void setIsAlly(bool ally){isAlly = ally;}; // Set whether the unit is an ally or not
        void attack(int, int); // Perform an attack on the specified unit
        int getHealth() const{return stats.health;}; // Get the current health of the unit
        void setHealth(int health){stats.health = health;}; // Set the current health of the unit
        bool isDead() const{return stats.health <= 0;}; // Check if the unit is dead
        void takeDamage(int damage){stats.health -= damage - stats.defense;}; // Take damage to the unit
        int getAttack() const{return stats.attack;}; // Get the attack power of the unit
        void setAttack(int attack){stats.attack = attack;}; // Set the attack power of the unit
        int getDefense() const{return stats.defense;}; // Get the defense power of the unit
        void setDefense(int defense){stats.defense = defense;}; // Set the defense power of the unit
        void learnSkill(const Skill& skill){ stats.skills.push_back(skill);}; 
        void unlearnSkill(const Skill& skill){
            stats.skills.erase(std::remove(stats.skills.begin(), stats.skills.end(), skill), stats.skills.end());  // Remove the specified skill from the unit's skills list
        }; // Remove a skill from the unit
        std::vector<Skill> getSkills() const{return stats.skills;}; // Get the skills learned by the unit
        Color getColor() const{return stats.color;}; // Get the color of the unit
        void setColor(Color color){stats.color = color;}; // Set the color of the unit
    private:
        int x, y; // Position of the unit on the grid
        STATE state; // Current state of the unit (e.g. idle, moving, selected)
        int moveRange; // Maximum distance the unit can move
        bool isAlly;
        Stats stats; // Placeholder for unit stats (health, attack, etc.)
        std::vector<Unit>* units;
        bool isMenuOpen = false;  // Track if the menu is open
        Action selectedAction = NONE;  // Track the selected action
        Action hoveredAction = NONE;  // Track the action currently hovered
        bool menuHovered = false;  // Track if the menu itself is being hovered
        bool buffer = false;
};

extern std::vector<Unit> units;


#endif // UNIT_HPP