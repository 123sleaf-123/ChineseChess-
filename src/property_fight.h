#ifndef PROPERTY_FIGHT_H
#define PROPERTY_FIGHT_H

#include "global.h"

typedef struct {
    int max_health;    // 最大生命值
    int health;        // 当前生命值
    int movement;      // 移动力
    int attack;        // 攻击
    int hitRate;       // 命中
    int critical;      // 必杀
    int attack_speed;   // 攻速
    int defense;       // 防御
    int magic_resist;   // 耐魔
    int evasion;       // 回避
    int min_range;         // 最近射程
    int max_range;         // 最远射程
} BattleProperty;

BattleProperty *initBattleProperty(int max_health, int health, int movement, int attack, int hitRate, int critical, int attack_speed, int defense, int magic_resist, int evasion, int range);
BattleProperty *initBattlePropertyV2(int max_health, int health, int movement, int attack, int hitRate, int critical, int attack_speed, int defense, int magic_resist, int evasion, int min_range, int max_range);
BattleProperty *initDefaultBattleProperty();
void freeBattleProperty(BattleProperty *battle_property);
int getMovement(BattleProperty *battle_property);
int getAttackMinRange(BattleProperty *battle_property);
void setAttackMinRange(BattleProperty *battle_property, int min_range);
int getAttackMaxRange(BattleProperty *battle_property);
void setAttackMaxRange(BattleProperty *battle_property, int max_range);
void printBattleProperty(BattleProperty *battle_property);

#endif