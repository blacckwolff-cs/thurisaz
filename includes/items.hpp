#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <string>

class character;


enum ItemType {
    CONSUMABLE,
    EQUIPMENT,
    KEY_ITEM
};

enum EquipmentType {
    WEAPON,
    ARMOR,
    ACCESSORY
};

enum WeaponType {
    SWORD,
    AXE,
    BOW,
    STAFF
};

enum ArmorType {
    HELMET,
    CHESTPLATE,
    LEGGINGS,
    BOOTS
};

enum AccessoryType {
    RING,
    NECKLACE,
    BRACER
};

class Item {
    public:
        Item() : name(""), price(0), type(ItemType::CONSUMABLE) {}
        Item(std::string name, int price, ItemType type) : name(name), price(price), type(type) {}
        std::string name;
        std::string description;
        int price;
        ItemType type;
        virtual ~Item() = default;  // Make it polymorphic
};

class Skill {
    public:
        Skill(std::string name, void (*effect)(character&, character&)) : name(name), effect(effect) {}
        std::string name;
        std::string description;
        void use(character& user, character& target){(void)user;  // Suppresses unused parameter warning
            (void)target;};
        void (*effect)(character&, character&); // Function pointer

};


class Consumable : public Item {
    public:
        Skill* skill;
};

class Equipment : public Item {
    public:
        Equipment() : attackBonus(0), defenseBonus(0), speedBonus(0)  {}
        float attackBonus;
        EquipmentType equipmentType;
        WeaponType weaponType;
        ArmorType armorType;
        AccessoryType accessoryType;
        float defenseBonus;
        float speedBonus;
};

class KeyItem : public Item {
    public:
        std::string location;
};


#endif