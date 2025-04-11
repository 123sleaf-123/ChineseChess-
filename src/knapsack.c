#include "knapsack.h"
#include "weapon.h"
#include <stdlib.h>

void initKnapsack(Knapsack *k, int capacity) {
    if (k == NULL) {
        k = malloc(sizeof(Knapsack));
    }
    k->weapons = malloc(sizeof(Weapon *) * capacity);
    k->capacity = capacity;
    k->size = 0; // Initialize size to 0
}

Knapsack *createKnapsack(int capacity) {
    Knapsack *k = malloc(sizeof(Knapsack));
    initKnapsack(k, capacity);
    return k;
}

Knapsack *createKnapsackDefault() {
    Knapsack *k = createKnapsack(5);               // Default capacity of 5
    addWeaponToKnapsack(k, createWeaponDefault()); // Default weapon
    addWeaponToKnapsack(k, createWeaponPrefab("sword"));
    addWeaponToKnapsack(k, createWeaponPrefab("bow"));
    addWeaponToKnapsack(k, createWeaponPrefab("lbow"));
    addWeaponToKnapsack(k, createWeaponPrefab("clb"));
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
            for (int j = i; j < k->size - 1; j++) {
                k->weapons[j] = k->weapons[j + 1]; // Shift weapons to the left
            }
            k->weapons[k->size - 1] = NULL; // Set the last weapon to NULL
            k->size--;                      // Decrease the size of the knapsack
            break;
        }
    }
}

void removeWeaponFromKnapsackByIndex(Knapsack *k, int index) {
    if (k == NULL || index < 0 || index >= k->capacity) {
        return;
    }
    k->weapons[index] = NULL;
    for (int j = index; j < k->capacity - 1; j++) {
        k->weapons[j] = k->weapons[j + 1]; // Shift weapons to the left
    }
    k->weapons[k->size - 1] = NULL; // Set the last weapon to NULL
    k->size--;                      // Decrease the size of the knapsack
}

void clearKnapsack(Knapsack *k) {
    if (k == NULL) {
        return;
    }
    for (int i = 0; i < k->capacity; i++) {
        k->weapons[i] = NULL;
    }
}

void displayKnapsackContents(Knapsack *k) {
    if (k == NULL) {
        return;
    }
    printf("Knapsack contents:\n");
    for (int i = 0; i < k->size; i++) {
        if (k->weapons[i] != NULL) {
            printf("Weapon %d: %s\n", i, k->weapons[i]->name);
        }
    }
}
