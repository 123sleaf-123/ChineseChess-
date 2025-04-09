#include "knapsack.h"

void initializeKnapsack(Knapsack *k, int capacity) {
    if (k == NULL) {
        k->weapons = malloc(sizeof(Weapon *) * capacity);
    }
    k->capacity = capacity;
    k->size = 0; // Initialize size to 0
}

Knapsack *createKnapsack(int capacity) {
    Knapsack *k = malloc(sizeof(Knapsack));
    initializeKnapsack(k, capacity);
    return k;
}

void addWeaponToKnapsack(Knapsack *k, Weapon *w) {
    if (k == NULL || w == NULL || k->capacity <= 0 || k->capacity <= k->size) {
        return;
    }
    k->weapons[k->size++] = w; // Add weapon to the knapsack
}

void removeWeaponFromKnapsack(Knapsack *k, Weapon *w) {
    if (k == NULL || w == NULL) {
        return;
    }
    for (int i = 0; i < k->capacity; i++) {
        if (k->weapons[i] == w) {
            k->weapons[i] = NULL; // Assuming name is a string, set it to NULL to indicate removal
            break;
        }
    }
}

void removeWeaponFromKnapsackByIndex(Knapsack *k, int index) {
    if (k == NULL || index < 0 || index >= k->capacity) {
        return;
    }
    k->weapons[index] = NULL;
}

void clearKnapsack(Knapsack *k) {
    if (k == NULL) {
        return;
    }
    for (int i = 0; i < k->capacity; i++) {
        k->weapons[i] = NULL;
    }
}
