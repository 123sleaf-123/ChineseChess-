#include "weapon.h"

void initWeapon(Weapon *weapon, char *name, int attack_power, int hit, int critical, int min_range, int max_range) {
    weapon->name = name;
    weapon->attack_power = attack_power;
    weapon->hit = hit;
    weapon->critical = critical;
    weapon->min_range = min_range;
    weapon->max_range = max_range;
}

Weapon *createWeapon(char *name, int attack_power, int hit, int critical, int min_range, int max_range) {
    Weapon *weapon = (Weapon *)malloc(sizeof(Weapon));
    initWeapon(weapon, name, attack_power, hit, critical, min_range, max_range);
    return weapon;
}

Weapon *createWeaponDeault() {
    return createWeapon("Default Weapon", 0, 0, 0, 0, 0);
}

Weapon *createWeaponPrefab(char *name) {
    Weapon *weapon = createWeaponDeault();
    if (strcmp(name, "sword") == 0) {
        weapon->name = "sword";
        weapon->attack_power = 5;
        weapon->hit = 10;
        weapon->critical = 0;
        weapon->min_range = 1;
        weapon->max_range = 1;
    } else if (strcmp(name, "bow") == 0) {
        weapon->name = "bow";
        weapon->attack_power = 5;
        weapon->hit = 10;
        weapon->critical = 0;
        weapon->min_range = 2;
        weapon->max_range = 2;
    } else if (strcmp(name, "lbow") == 0) {
        weapon->name = "long bow";
        weapon->attack_power = 5;
        weapon->hit = 10;
        weapon->critical = 0;
        weapon->min_range = 2;
        weapon->max_range = 3;
    } else {
        free(weapon);
        return NULL; // Invalid name
    
    }
    return weapon;
}