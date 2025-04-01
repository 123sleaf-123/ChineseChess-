#include "property_fight.h"

BattleProperty *initBattleProperty(int max_health, int health, int movement, int attack, int hitRate, int critical, int attack_speed, int defense, int magic_resist, int evasion, int range) {
    BattleProperty *battle_property = (BattleProperty *)malloc(sizeof(BattleProperty));
    battle_property->max_health = max_health;
    battle_property->health = health;
    battle_property->movement = movement;
    battle_property->attack = attack;
    battle_property->hitRate = hitRate;
    battle_property->critical = critical;
    battle_property->attack_speed = attack_speed;
    battle_property->defense = defense;
    battle_property->magic_resist = magic_resist;
    battle_property->evasion = evasion;
    battle_property->range = range;
    return battle_property;
}

BattleProperty *initDefaultBattleProperty() {
    return initBattleProperty(27, 27, 4, 13, 6, 9, 8, 8, 6, 6, 1);
}

void freeBattleProperty(BattleProperty *battle_property) {
    free(battle_property);
}

int getMovement(BattleProperty *battle_property) {
    return battle_property->movement;
}

int getAttackRange(BattleProperty *battle_property) {
    return battle_property->range;
}

void printBattleProperty(BattleProperty *battle_property) {
    if (battle_property == NULL) return;
    printf("战斗属性: 生命 %d/%d, 移动力 %d, 攻击 %d, 命中 %d, 必杀 %d, 攻速 %d, 防御 %d, 耐魔 %d, 回避 %d, 射程 %d\n",
           battle_property->health, battle_property->max_health, battle_property->movement, battle_property->attack,
           battle_property->hitRate, battle_property->critical, battle_property->attack_speed,
           battle_property->defense, battle_property->magic_resist, battle_property->evasion, battle_property->range);
}