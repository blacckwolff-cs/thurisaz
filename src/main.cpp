#pragma onceclude "../includes/dungeon.hpp"
#include "../includes/game.hpp"
#include "../includes/Character.hpp"
#include "../includes/items.hpp"
#include "../includes/skills.hpp"


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RPG Game");
    SetTargetFPS(60);
    Character player(100, 10.0f, 5.0f, 1.0f, 0, 1, 0, 100);
    Character enemy(100, 10.0f, 5.0f, 1.0f, 0, 1, 0, 100);
    player.name = "Hero";
    enemy.name = "Goblin";
    player.AddEnemy(std::make_shared<Character>(enemy));
    player.inventory.push_back(Item("Health Potion", 10, ItemType::CONSUMABLE));
    player.LearnSkill(Skill("Slash", slash));
    player.LearnSkill(Skill("Fireball", fireball));
    player.LearnSkill(Skill("Heal", heal));
    player.party.push_back(std::make_shared<Character>(50, 8.0f, 4.0f, 1.0f, 0, 1, 0, 50));
    player.DisplayStats();
    player.UseSkill(0, enemy); // Use Slash on Goblin
    enemy.DisplayStats();
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        player.DisplayStats();
        //enemy.DisplayStats();
        EndDrawing();
    }
}