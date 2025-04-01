#include "../includes/dungeon.hpp"
#include "../includes/game.hpp"
#include "../includes/character.hpp"
#include "../includes/items.hpp"


void slash(character& user, character& target) {
    int damage = user.stats.attack * 2 - target.stats.defense;
    if (damage < 0) damage = 0;
    target.TakeDamage(damage);
}

void fireball(character& user, character& target) {
    int damage = user.stats.attack * 3 - target.stats.defense;
    if (damage < 0) damage = 0;
    target.TakeDamage(damage);
}

void heal(character& user, character& target) {
    user.Heal(user.stats.maxHealth / 4);
}

int main(){
    return 0;
    character player(100, 10.0f, 5.0f, 1.0f, 0, 1, 0, 100);
    player.name = "Hero";
    player.inventory.push_back(Item("Health Potion", 10, ItemType::CONSUMABLE));
    player.LearnSkill(Skill("Slash", slash));
    player.LearnSkill(Skill("Fireball", fireball));
    player.LearnSkill(Skill("Heal", heal));
    player.party.push_back(std::make_shared<character>(50, 8.0f, 4.0f, 1.0f, 0, 1, 0, 50));
}