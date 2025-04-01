#include "../includes/character.hpp"


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
