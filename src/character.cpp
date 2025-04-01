#include "../includes/character.hpp"
#include <algorithm>


// Stats constructor implementation
Stats::Stats(int health, float attack, float defense, float speed, int experience, int level, int gold, int maxHealth)
    : health(health), attack(attack), defense(defense), speed(speed), experience(experience), level(level), gold(gold), maxHealth(maxHealth) {}

// character constructor implementation
character::character(int health, float attack, float defense, float speed, int experience, int level, int gold, int maxHealth)
    : stats(health, attack, defense, speed, experience, level, gold, maxHealth) {}

// TakeDamage function implementation
void character::TakeDamage(int damage) {
    stats.health -= damage;
    if (stats.health < 0) stats.health = 0;
}

// Heal function implementation
void character::Heal(int amount) {
    stats.health += amount;
    if (stats.health > stats.maxHealth) stats.health = stats.maxHealth;
}

// Attack function implementation
void character::Attack(character& target) {
    int damage = stats.attack - target.stats.defense;
    if (damage < 0) damage = 0;
    target.TakeDamage(damage);
}

// IsAlive function implementation
bool character::IsAlive() const {
    return stats.health > 0;
}

// UseSkill function implementation
void character::UseSkill(int skillIndex, character& target) {
    if (skillIndex >= 0 && skillIndex < skills.size()) {
        skills[skillIndex].use(*this, target);
    }
}

// DisplayStats function implementation
void character::DisplayStats() const {
    std::cout << "Name: " << name << " | HP: " << stats.health << "/" << stats.maxHealth
              << " | Level: " << stats.level << " | Attack: " << stats.attack
              << " | Defense: " << stats.defense << std::endl;
}

void character::LearnSkill(const Skill& skill) {
    skills.push_back(skill);
}

void character::AddPartyMember(const std::shared_ptr<character>& member) {
    party.push_back(member);
}

void character::AddEnemy(const std::shared_ptr<character>& enemy) {
    enemies.push_back(enemy);
}

void character::LevelUp() {
    stats.level++;
    stats.maxHealth += 10;
    stats.health = stats.maxHealth;
    stats.experience = 0;
    stats.gold += 10;
}

void character::GainExperience(int amount) {
    stats.experience += amount;
    while (stats.experience >= stats.level * 100) {
        LevelUp();
    }
}

void character::EarnGold(int amount) {
    stats.gold += amount;
}

void character::SpendGold(int amount) {
    if (stats.gold >= amount) {
        stats.gold -= amount;
    }
}

void character::EquipItem(const std::shared_ptr<Item>& item) {
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
void character::UnequipItem(const Item& item) {
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
void character::UnlearnSkill(const Skill& skill) {
    // Logic to unlearn skill
    auto it = std::remove_if(skills.begin(), skills.end(), [&](const Skill& s) { return s.name == skill.name; });
}
void character::AddToInventory(const Item& item) {
    inventory.push_back(item);
}
void character::RemoveFromInventory(const Item& item) {
    inventory.erase(std::remove_if(inventory.begin(), inventory.end(), [&](const Item& i) { return i.name == item.name; }), inventory.end());
}
