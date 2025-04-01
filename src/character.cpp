#include "../includes/Character.hpp"
#include <algorithm>
#include <raylib.h>


// Stats constructor implementation
Stats::Stats(int health, float attack, float defense, float speed, int experience, int level, int gold, int maxHealth)
    : health(health), attack(attack), defense(defense), speed(speed), experience(experience), level(level), gold(gold), maxHealth(maxHealth) {}

// Character constructor implementation
Character::Character(int health, float attack, float defense, float speed, int experience, int level, int gold, int maxHealth)
    : stats(health, attack, defense, speed, experience, level, gold, maxHealth) {}

// TakeDamage function implementation
void Character::TakeDamage(int damage) {
    stats.health -= damage;
    if (stats.health < 0) stats.health = 0;
}



// Heal function implementation
void Character::Heal(int amount) {
    stats.health += amount;
    if (stats.health > stats.maxHealth) stats.health = stats.maxHealth;
}

// Attack function implementation
void Character::Attack(Character& target) {
    int damage = stats.attack - target.stats.defense;
    if (damage < 0) damage = 0;
    target.TakeDamage(damage);
}

// IsAlive function implementation
bool Character::IsAlive() const {
    return stats.health > 0;
}

// UseSkill function implementation
void Character::UseSkill(int skillIndex, Character& target) {
    if (skillIndex >= 0 && skillIndex < skills.size()) {
        skills[skillIndex].use(*this, target);
    }
}

// DisplayStats function implementation
void Character::DisplayStats() const {
    DrawText(TextFormat("Name: %s\nHealth: %d/%d\nAttack: %.1f\nDefense: %.1f\nSpeed: %.1f\nExperience: %d\nLevel: %d\nGold: %d",
        name.c_str(),
        stats.health, stats.maxHealth,
        stats.attack,
        stats.defense,
        stats.speed,
        stats.experience,
        stats.level,
        stats.gold), 0, 0, 20, BLACK);


}
void Character::LearnSkill(const Skill& skill) {
    skills.push_back(skill);
}

void Character::AddPartyMember(const std::shared_ptr<Character>& member) {
    party.push_back(member);
}

void Character::AddEnemy(const std::shared_ptr<Character>& enemy) {
    enemies.push_back(enemy);
}

void Character::LevelUp() {
    stats.level++;
    stats.maxHealth += 10;
    stats.health = stats.maxHealth;
    stats.experience = 0;
    stats.gold += 10;
}

void Character::GainExperience(int amount) {
    stats.experience += amount;
    while (stats.experience >= stats.level * 100) {
        LevelUp();
    }
}

void Character::EarnGold(int amount) {
    stats.gold += amount;
}

void Character::SpendGold(int amount) {
    if (stats.gold >= amount) {
        stats.gold -= amount;
    }
}

void Character::EquipItem(const std::shared_ptr<Item>& item) {
    switch(item->type){
        case ItemType::EQUIPMENT:
            if (auto equipment = std::dynamic_pointer_cast<Equipment>(item)) {
                switch(equipment->equipmentType) {
                    case EquipmentType::WEAPON:
                        // Logic to equip weapon
                        this->equipment[0] = *equipment; // Assuming first slot is for weapon
                        break;
                    case EquipmentType::ARMOR:
                        // Logic to equip armor
                        switch(equipment->armorType) {
                            case ArmorType::HELMET:
                                this->equipment[1] = *equipment; // Assuming second slot is for helmet
                                break;
                            case ArmorType::CHESTPLATE:
                                this->equipment[2] = *equipment; // Assuming third slot is for chestplate
                                break;
                            case ArmorType::LEGGINGS:
                                this->equipment[3] = *equipment; // Assuming fourth slot is for leggings
                                break;
                            case ArmorType::BOOTS:
                                this->equipment[4] = *equipment; // Assuming fifth slot is for boots
                                break;
                        }
                        break;
                    case EquipmentType::ACCESSORY:
                        // Logic to equip accessory
                        switch(equipment->accessoryType) {
                            case AccessoryType::RING:
                                this->equipment[5] = *equipment; // Assuming sixth slot is for ring
                                break;
                            case AccessoryType::NECKLACE:
                                this->equipment[6] = *equipment; // Assuming seventh slot is for necklace
                                break;
                            case AccessoryType::BRACER:
                                this->equipment[7] = *equipment; // Assuming eighth slot is for bracer
                                break;
                        }
                        break;
                }
                stats.attack += equipment->attackBonus;
                stats.defense += equipment->defenseBonus;
                stats.speed += equipment->speedBonus;
            }
            break;
    }
}
void Character::UnequipItem(const Item& item) {
    for(auto& equipment : equipment) {
        if(equipment.name == item.name) {
            stats.attack -= equipment.attackBonus;
            stats.defense -= equipment.defenseBonus;
            stats.speed -= equipment.speedBonus;
            equipment = Equipment(); // Reset the slot
            break;
        }
    }
}
void Character::UnlearnSkill(const Skill& skill) {
    // Logic to unlearn skill
    auto it = std::remove_if(skills.begin(), skills.end(), [&](const Skill& s) { return s.name == skill.name; });
}
void Character::AddToInventory(const Item& item) {
    inventory.push_back(item);
}
void Character::RemoveFromInventory(const Item& item) {
    inventory.erase(std::remove_if(inventory.begin(), inventory.end(), [&](const Item& i) { return i.name == item.name; }), inventory.end());
}
