#ifndef WEAPON_H
#define WEAPON_H

#include "property_basic.h"

typedef struct {
    char *name;
    BasicProperty *basic_property;
} Weapon;

void initWeapon(Weapon *weapon, char *name, BasicProperty *basic_property);
Weapon *createWeapon(char *name, BasicProperty *basic_property);

#endif