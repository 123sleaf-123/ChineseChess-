#ifndef CHARACTER_H
#define CHARACTER_H

#include "knapsack.h"
#include "property_basic.h"
#include "property_fight.h"
#include "weapon.h"

typedef struct {
    char name[20];  // Character name
    Weapon *weapon; // Character weapon
    BasicProperty *property_basic;
    BattleProperty *property_fight;
    Knapsack *knapsack; // Character's knapsack
} Character;

void initCharacter(Character *character, const char *name, BasicProperty *property_basic,
                   BattleProperty *property_fight);
void initCharacterV2(Character *character, const char *name, BasicProperty *property_basic);
void initCharacterV3(Character *character, const char *name, BasicProperty *property_basic, Knapsack *knapsack);
Character *createCharacter(const char *name, BasicProperty *property_basic, BattleProperty *property_fight);
Character *createCharacterV2(const char *name, BasicProperty *property_basic);
Character *createCharacterV3(const char *name, BasicProperty *property_basic, Knapsack *knapsack);
Character *createCharacterDeault();
BasicProperty *getCharacterBasicProperty(Character *character);
BattleProperty *getCharacterBattleProperty(Character *character);

void equipWeapon(Character *character, Weapon *weapon);
void unequipWeapon(Character *character);

#endif // CHARACTER_H