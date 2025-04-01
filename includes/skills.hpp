#pragma once

#include "../includes/character.hpp"


void slash(Character& user, Character& target) {
    std::cout << user.name << " slashes " << target.name << "!" << std::endl;
    int damage = user.stats.attack * 2 - target.stats.defense;
    if (damage < 0) damage = 0;
    target.TakeDamage(damage);
}

void fireball(Character& user, Character& target) {
    int damage = user.stats.attack * 3 - target.stats.defense;
    if (damage < 0) damage = 0;
    target.TakeDamage(damage);
}

void heal(Character& user, Character& target) {
    user.Heal(user.stats.maxHealth / 4);
}
