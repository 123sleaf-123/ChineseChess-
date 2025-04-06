#include "property_basic.h"

void initBasicProperty(BasicProperty *property, int strength, int magic, int skill, int speed, int luck, int defense, int magic_defense, int charm, int movement, int health, int level, int experience) {
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
}

BasicProperty *createBasicPropertyDeault() {
    BasicProperty *new_property = (BasicProperty *)malloc(sizeof(BasicProperty));
    if (new_property == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    initBasicProperty(new_property, 10, 10, 10, 10, 10, 10, 10, 10, 10, 100, 1, 0);
    
    return new_property;
}