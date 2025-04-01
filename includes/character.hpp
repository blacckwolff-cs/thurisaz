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
    std::vector<Equipment> equipment;  // Equipped items (for Equipment items)
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
    void EquipItem(const std::shared_ptr<Item>&);
    void UnequipItem(const Item& item);
    void AddPartyMember(const std::shared_ptr<character>& character);
    void AddEnemy(const std::shared_ptr<character>& character);
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
