#include "property_fight.h"

void initBattleProperty(BattleProperty *battle_property, int max_health, int health, int movement, int attack, int hit_rate, int critical, int attack_speed, int defense, int magic_resist, int evasion, int range) {
    battle_property->max_health = max_health;
    battle_property->health = health;
    battle_property->movement = movement;
    battle_property->attack = attack;
    battle_property->hit_rate = hit_rate;
    battle_property->critical = critical;
    battle_property->attack_speed = attack_speed;
    battle_property->defense = defense;
    battle_property->magic_resist = magic_resist;
    battle_property->evasion = evasion;
    battle_property->min_range = range;
    battle_property->max_range = range;
}

void initBattlePropertyV2(BattleProperty *battle_property, int max_health, int health, int movement, int attack, int hit_rate, int critical, int attack_speed, int defense, int magic_resist, int evasion, int min_range, int max_range) {
    initBattleProperty(battle_property, max_health, health, movement, attack, hit_rate, critical, attack_speed, defense, magic_resist, evasion, min_range);
    battle_property->max_range = max_range;
}

BattleProperty *createBattlePropertyDefault() {
    BattleProperty *battle_property = (BattleProperty *)malloc(sizeof(BattleProperty));
    if (battle_property == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    initBattlePropertyV2(battle_property, 27, 27, 4, 13, 6, 9, 8, 8, 6, 6, 0, 0);
    return battle_property;
}

BattleProperty *createBattlePropertyFromBasicProperty(BasicProperty *basic_property) {
    BattleProperty *battle_property = (BattleProperty *)malloc(sizeof(BattleProperty));
    if (battle_property == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    initBattlePropertyV2(battle_property, basic_property->health,
                         basic_property->health, basic_property->movement,
                         basic_property->strength, basic_property->skill,
                         basic_property->charm, basic_property->speed,
                         basic_property->defense, basic_property->magic_defense,
                         basic_property->speed,
                         0, 0);
    return battle_property;
}

void freeBattleProperty(BattleProperty *battle_property) {
    free(battle_property);
}

int getHealth(BattleProperty *battle_property) {
    return battle_property->health;
}

void setHealth(BattleProperty *battle_property, int health) {
    battle_property->health = health > battle_property->max_health ? battle_property->max_health : health;
}

int getMovement(BattleProperty *battle_property) {
    return battle_property->movement;
}

void setMovement(BattleProperty *battle_property, int movement) {
    battle_property->movement = movement;
}

int getAttack(BattleProperty *battle_property) {
    return battle_property->attack;
}

void setAttack(BattleProperty *battle_property, int attack) {
    battle_property->attack = attack;
}

int getHitRate(BattleProperty *battle_property) {
    return battle_property->hit_rate;
}

void setHitRate(BattleProperty *battle_property, int hit_rate) {
    battle_property->hit_rate = hit_rate;
}

int getCritical(BattleProperty *battle_property) {
    return battle_property->critical;
}

void setCritical(BattleProperty *battle_property, int critical) {
    battle_property->critical = critical;
}

int getAttackSpeed(BattleProperty *battle_property) {
    return battle_property->attack_speed;
}

void setAttackSpeed(BattleProperty *battle_property, int attack_speed) {
    battle_property->attack_speed = attack_speed;
}

int getDefense(BattleProperty *battle_property) {
    return battle_property->defense;
}

void setDefense(BattleProperty *battle_property, int defense) {
    battle_property->defense = defense;
}

int getMagicResist(BattleProperty *battle_property) {
    return battle_property->magic_resist;
}

void setMagicResist(BattleProperty *battle_property, int magic_resist) {
    battle_property->magic_resist = magic_resist;
}

int getEvasion(BattleProperty *battle_property) {
    return battle_property->evasion;
}

void setEvasion(BattleProperty *battle_property, int evasion) {
    battle_property->evasion = evasion;
}

int getAttackMinRange(BattleProperty *battle_property) {
    return battle_property->min_range;
}

void setAttackMinRange(BattleProperty *battle_property, int min_range) {
    battle_property->min_range = min_range;
}

int getAttackMaxRange(BattleProperty *battle_property) {
    return battle_property->max_range;
}

void setAttackMaxRange(BattleProperty *battle_property, int max_range) {
    battle_property->max_range = max_range;
}

void printBattleProperty(BattleProperty *battle_property) {
    if (battle_property == NULL) return;
    printf("战斗属性: 生命 %d/%d, 移动力 %d, 攻击 %d, 命中 %d, 必杀 %d, 攻速 %d, 防御 %d, 耐魔 %d, 回避 %d, 射程 %d-%d\n",
           battle_property->health, battle_property->max_health, battle_property->movement, battle_property->attack,
           battle_property->hit_rate, battle_property->critical, battle_property->attack_speed,
           battle_property->defense, battle_property->magic_resist, battle_property->evasion, battle_property->min_range, battle_property->max_range);
}