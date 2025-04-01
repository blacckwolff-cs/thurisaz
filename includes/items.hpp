#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <string>
#include "skills.hpp"



enum ItemType {
    CONSUMABLE,
    EQUIPMENT,
    KEY_ITEM
};

class Item {
    public:
        std::string name;
        ItemType type;
        int price;
};

class Consumable : public Item {
    public:
        Skill* skill;
};

class Equipment : public Item {
    public:
        int attackBonus;
        int defenseBonus;
        int speedBonus;
};

class KeyItem : public Item {
    public:
        std::string location;
};


#endif