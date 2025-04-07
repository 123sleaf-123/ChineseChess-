#ifndef CHARACTER_H
#define CHARACTER_H

#include "property_basic.h"
#include "property_fight.h"

typedef struct {
    char name[20];  // Character name
    BasicProperty *property_basic;
    BattleProperty *property_fight;
} Character;

void initCharacter(Character *character, const char *name, BasicProperty *property_basic, BattleProperty *property_fight);
Character *createCharacter(const char *name, BasicProperty *property_basic, BattleProperty *property_fight);
Character *createCharacterDeault();
BasicProperty *getCharacterBasicProperty(Character *character);
BattleProperty *getCharacterBattleProperty(Character *character);

#endif // CHARACTER_H