#include "knapsack.h"

void initializeKnapsack(Knapsack *k, int capacity) {
    if (k == NULL) {
        k->weapons = malloc(sizeof(Weapon) * capacity);
    }
    k->capacity = capacity;
}

Knapsack *createKnapsack(int capacity) {
    Knapsack *k = malloc(sizeof(Knapsack));
    initializeKnapsack(k, capacity);
    return k;
}

void addWeaponToKnapsack(Knapsack *k, Weapon *w) {
    if (k == NULL || w == NULL) {
        return;
    }
    for (int i = 0; i < k->capacity; i++) {
        if (k->weapons[i].name == NULL) {
            k->weapons[i] = *w;
            break;
        }
    }
}

void removeWeaponFromKnapsack(Knapsack *k, Weapon *w) {
    if (k == NULL || w == NULL) {
        return;
    }
    for (int i = 0; i < k->capacity; i++) {
        if (strcmp(k->weapons[i].name, w->name) == 0) {
            k->weapons[i].name = NULL;
            break;
        }
    }
}

void removeWeaponFromKnapsackByIndex(Knapsack *k, int index) {
    if (k == NULL || index < 0 || index >= k->capacity) {
        return;
    }
    k->weapons[index].name = NULL;
}

void clearKnapsack(Knapsack *k) {
    if (k == NULL) {
        return;
    }
    for (int i = 0; i < k->capacity; i++) {
        k->weapons[i].name = NULL;
    }
}

