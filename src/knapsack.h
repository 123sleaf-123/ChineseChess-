#ifndef KNAPSACK_H
#define KNAPSACK_H

#include "weapon.h"

typedef struct {
    Weapon *weapons;
    int capacity;
} Knapsack;

void initializeKnapsack(Knapsack *k, int capacity);
Knapsack *createKnapsack(int capacity);
void addWeaponToKnapsack(Knapsack *k, Weapon *w);
void removeWeaponFromKnapsack(Knapsack *k, Weapon *w);
void removeWeaponFromKnapsackByIndex(Knapsack *k, int index);
void clearKnapsack(Knapsack *k);
void displayKnapsackContents(Knapsack *k);

#endif // KNAPSACK_H