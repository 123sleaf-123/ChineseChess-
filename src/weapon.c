#include "weapon.h"

void initWeapon(Weapon *weapon, char *name, BasicProperty *basic_property, int min_range, int max_range) {
    weapon->name = name;
    weapon->basic_property = basic_property;
    weapon->min_range = min_range;
    weapon->max_range = max_range;
}

Weapon *createWeapon(char *name, BasicProperty *basic_property, int min_range, int max_range) {
    Weapon *weapon = (Weapon *)malloc(sizeof(Weapon));
    initWeapon(weapon, name, basic_property, min_range, max_range);
    return weapon;
}