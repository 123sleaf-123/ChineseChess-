#include "weapon.h"

void initWeapon(Weapon *weapon, char *name, BasicProperty *basic_property) {
    weapon->name = name;
    weapon->basic_property = basic_property;
}

Weapon *createWeapon(char *name, BasicProperty *basic_property) {
    Weapon *weapon = (Weapon *)malloc(sizeof(Weapon));
    initWeapon(weapon, name, basic_property);
    return weapon;
}