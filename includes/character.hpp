#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <memory>
#include <string>
#include "items.hpp"
#include <iostream>
#include <algorithm>
#include <raylib.h>  // Include raylib for graphics and window management

// Enum for Character Class
enum class CharacterClass {
    WARRIOR,
    MAGE,
    ROGUE
};

// Stats struct to hold Character stats
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
class Character {
public:
    Stats stats;
    std::string name;
    std::string description;
    CharacterClass CharacterClass;
    std::vector<Item> inventory;
    std::vector<Skill> skills;
    std::vector<Equipment> equipment;  // Equipped items (for Equipment items)
    std::vector<std::shared_ptr<Character>> party;  // Party members (for RPG parties)
    std::vector<std::shared_ptr<Character>> enemies;  // Enemies in combat

    // Constructor for Character creation
    Character(int health, float attack, float defense, float speed, int experience, int level, int gold, int maxHealth);

    // Combat functions
    void TakeDamage(int damage);
    void Heal(int amount);
    void Attack(Character& target);
    bool IsAlive() const;
    void UseSkill(int skillIndex, Character& target);
    void DisplayStats() const;
    void EquipItem(const std::shared_ptr<Item>&);
    void UnequipItem(const Item& item);
    void AddPartyMember(const std::shared_ptr<Character>& Character);
    void AddEnemy(const std::shared_ptr<Character>& Character);
    void LearnSkill(const Skill& skill);
    void UnlearnSkill(const Skill& skill);
    void AddToInventory(const Item& item);
    void RemoveFromInventory(const Item& item);
    void LevelUp();
    void GainExperience(int amount);
    void SpendGold(int amount);
    void EarnGold(int amount);

};

#endif // PLAYER_HPP
