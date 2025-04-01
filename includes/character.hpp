#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <memory>
#include <string>
#include "items.hpp"
#include <iostream>

// Enum for Character Class
enum class CharacterClass {
    WARRIOR,
    MAGE,
    ROGUE
};

// Stats struct to hold character stats
struct Stats {
    Stats(int health, float attack, float defense, float speed, int experience, int level, int gold, int maxHealth);
    
    int health;
    float attack;
    float defense;
    float speed;
    int experience;
    int level;
    int gold;
    int maxHealth;
};

// Character class definition
class character {
public:
    Stats stats;
    std::string name;
    std::string description;
    CharacterClass characterClass;
    std::vector<Item> inventory;
    std::vector<Skill> skills;
    std::vector<std::shared_ptr<character>> party;  // Party members (for RPG parties)
    std::vector<std::shared_ptr<character>> enemies;  // Enemies in combat

    // Constructor for character creation
    character(int health, float attack, float defense, float speed, int experience, int level, int gold, int maxHealth);

    // Combat functions
    void TakeDamage(int damage);
    void Heal(int amount);
    void Attack(character& target);
    bool IsAlive() const;
    void UseSkill(int skillIndex, character& target);
    void DisplayStats() const;
};

#endif // PLAYER_HPP
