#include "unit.hpp"

void fireball(Unit& attacker, Unit& target) {
    int aoeRadius = 100;
    int damage = 30;

    // Fireball effect: hit target and surrounding units in AOE
    std::cout << "Fireball cast by " << " at " << target.getX() << ", " << target.getY() << "!\n";

    // Loop through all units to apply damage within AOE
    for (Unit& unit : units) {
        int dx = unit.getX() - target.getX();
        int dy = unit.getY() - target.getY();
        int distanceSquared = dx * dx + dy * dy;

        if (distanceSquared <= aoeRadius * aoeRadius) {
            std::cout << "Fireball hits unit at " << unit.getX() << ", " << unit.getY() << " for " << damage << " damage!\n";
            unit.takeDamage(damage);
        }
    }
}
