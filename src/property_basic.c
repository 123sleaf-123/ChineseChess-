#include "property_basic.h"

void initBasicProperty(BasicProperty *property, int strength, int magic, int skill, int speed, int luck, int defense, int magic_defense, int charm, int movement, int health, int level, int experience, int attack_range) {
    property->strength = strength;
    property->magic = magic;
    property->skill = skill;
    property->speed = speed;
    property->luck = luck;
    property->defense = defense;
    property->magic_defense = magic_defense;
    property->charm = charm;
    property->movement = movement;
    property->health = health;
    property->level = level;
    property->experience = experience;
    property->attack_range = attack_range;
}

BasicProperty *createBasicPropertyDeault() {
    BasicProperty *new_property = (BasicProperty *)malloc(sizeof(BasicProperty));
    if (new_property == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    initBasicProperty(new_property, 10, 10, 10, 10, 10, 10, 10, 10, 10, 100, 1, 0, 0);
    
    return new_property;
}

void addBasicProperty(BasicProperty *target, BasicProperty *source) {
    target->strength += source->strength;
    target->magic += source->magic;
    target->skill += source->skill;
    target->speed += source->speed;
    target->luck += source->luck;
    target->defense += source->defense;
    target->magic_defense += source->magic_defense;
    target->charm += source->charm;
    target->movement += source->movement;
    target->health += source->health;
    target->level += source->level;
    target->experience += source->experience;
    target->attack_range += source->attack_range;
}