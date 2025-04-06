#ifndef CHARACTER_H
#define CHARACTER_H

#include "property_basic.h"
#include "property_fight.h"

typedef struct {
    char name[20];  // Character name
    BasicProperty *property_basic;
    BattleProperty *property_fight;
} Character;

#endif // CHARACTER_H