#include "character.h"
#include "property_basic.h"
#include "property_fight.h"

void initCharacter(Character *character, const char *name, BasicProperty *property_basic,
                   BattleProperty *property_fight) {
    strcpy(character->name, name);
    character->property_basic = property_basic;
    character->property_fight = property_fight;
}

// 从基础属性生成战斗属性
void initCharacterV2(Character *character, const char *name, BasicProperty *property_basic) {
    strcpy(character->name, name);
    character->property_basic = property_basic;
    character->property_fight = createBattlePropertyFromBasicProperty(property_basic);
}

void initCharacterV3(Character *character, const char *name, BasicProperty *property_basic,
                     BattleProperty *property_fight, Knapsack *knapsack) {
    strcpy(character->name, name);
    character->property_basic = property_basic;
    character->property_fight = property_fight;
    character->knapsack = knapsack;
}

Character *createCharacter(const char *name, BasicProperty *property_basic, BattleProperty *property_fight) {
    Character *character = (Character *)malloc(sizeof(Character));
    if (character == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    initCharacter(character, name, property_basic, property_fight);
    return character;
}

Character *createCharacterDeault() {
    Character *new_character = createCharacter("Default", createBasicPropertyDeault(), createBattlePropertyDefault());
    return new_character;
}

// Getters & Setters
BasicProperty *getCharacterBasicProperty(Character *character) {
    return character->property_basic;
}

BattleProperty *getCharacterBattleProperty(Character *character) {
    return character->property_fight;
}

void equipWeapon(Character *character, Weapon *weapon) {
    character->weapon = weapon;
    if (weapon != NULL) {
        character->property_fight->attack += weapon->attack_power;
        character->property_fight->hit_rate += weapon->hit;
        character->property_fight->critical += weapon->critical;
        character->property_fight->min_range = weapon->min_range;
        character->property_fight->max_range = weapon->max_range + character->property_basic->attack_range;
    }
}

void unequipWeapon(Character *character) {
    if (character->weapon != NULL) {
        character->property_fight->attack -= character->weapon->attack_power;
        character->property_fight->hit_rate -= character->weapon->hit;
        character->property_fight->critical -= character->weapon->critical;
        character->property_fight->min_range = 0;
        character->property_fight->max_range = 0;
        free(character->weapon);
        character->weapon = NULL;
    }
}