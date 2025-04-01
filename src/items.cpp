#include "../includes/items.hpp"

void Skill::use(Character& user, Character& target) {
    effect(user, target);
}