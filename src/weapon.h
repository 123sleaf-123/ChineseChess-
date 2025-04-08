#ifndef WEAPON_H
#define WEAPON_H

#include "property_basic.h"

typedef struct {
    char *name;
    BasicProperty *basic_property;
    int min_range;
    int max_range;
} Weapon;

void initWeapon(Weapon *weapon, char *name, BasicProperty *basic_property, int min_range, int max_range);
Weapon *createWeapon(char *name, BasicProperty *basic_property, int min_range, int max_range);

#endif