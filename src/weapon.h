#ifndef WEAPON_H
#define WEAPON_H

#include "global.h"

typedef struct {
    char *name;
    int attack_power;
    int hit;
    int critical;
    int min_range;
    int max_range;
} Weapon;

void initWeapon(Weapon *weapon, char *name, int attack_power, int hit, int critical, int min_range, int max_range);
Weapon *createWeapon(char *name, int attack_power, int hit, int critical, int min_range, int max_range);
Weapon *createWeaponDefault();
Weapon *createWeaponPrefab(char *name);

#endif