#include "character.h"
#include "property_basic.h"

void initCharacter(Character *character, const char *name, BasicProperty *property_basic, BattleProperty *property_fight) {
    strcpy(character->name, name);
    character->property_basic = property_basic;
    character->property_fight = property_fight;
}

Character *createCharacter(const char *name, BasicProperty *property_basic, BattleProperty *property_fight) {
    Character *character = (Character *)malloc(sizeof(Character));
    if (character == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    initCharacter(character, name, property_basic, property_fight);
    return character;
}

Character *createCharacterDeault() {
    Character *new_character = createCharacter("Default", createBasicPropertyDeault(), initDefaultBattleProperty());
    return new_character;
}

// Getters & Setters
BasicProperty *getCharacterBasicProperty(Character *character) {
    return character->property_basic;
}

BattleProperty *getCharacterBattleProperty(Character *character) {
    return character->property_fight;
}