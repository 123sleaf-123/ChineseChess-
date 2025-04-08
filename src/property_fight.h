#ifndef PROPERTY_FIGHT_H
#define PROPERTY_FIGHT_H

#include "global.h"
#include "property_basic.h"

typedef struct {
    int max_health;    // 最大生命值
    int health;        // 当前生命值
    int movement;      // 移动力
    int attack;        // 攻击
    int hit_rate;       // 命中
    int critical;      // 必杀
    int attack_speed;   // 攻速
    int defense;       // 防御
    int magic_resist;   // 耐魔
    int evasion;       // 回避
    int min_range;         // 最近射程
    int max_range;         // 最远射程
} BattleProperty;

void initBattleProperty(BattleProperty *battle_property, int max_health, int health, int movement, int attack, int hit_rate, int critical, int attack_speed, int defense, int magic_resist, int evasion, int range);
void initBattlePropertyV2(BattleProperty *battle_property, int max_health, int health, int movement, int attack, int hit_rate, int critical, int attack_speed, int defense, int magic_resist, int evasion, int min_range, int max_range);
BattleProperty *createBattlePropertyDefault();
BattleProperty *createBattlePropertyFromBasicProperty(BasicProperty *basic_property);
void freeBattleProperty(BattleProperty *battle_property);
int getHealth(BattleProperty *battle_property);
void setHealth(BattleProperty *battle_property, int health);
int getMovement(BattleProperty *battle_property);
void setMovement(BattleProperty *battle_property, int movement);
int getAttack(BattleProperty *battle_property);
void setAttack(BattleProperty *battle_property, int attack);
int getHitRate(BattleProperty *battle_property);
void setHitRate(BattleProperty *battle_property, int hit_rate);
int getCritical(BattleProperty *battle_property);
void setCritical(BattleProperty *battle_property, int critical);
int getAttackSpeed(BattleProperty *battle_property);
void setAttackSpeed(BattleProperty *battle_property, int attack_speed);
int getDefense(BattleProperty *battle_property);
void setDefense(BattleProperty *battle_property, int defense);
int getMagicResist(BattleProperty *battle_property);
void setMagicResist(BattleProperty *battle_property, int magic_resist);
int getEvasion(BattleProperty *battle_property);
void setEvasion(BattleProperty *battle_property, int evasion);
int getAttackMinRange(BattleProperty *battle_property);
void setAttackMinRange(BattleProperty *battle_property, int min_range);
int getAttackMaxRange(BattleProperty *battle_property);
void setAttackMaxRange(BattleProperty *battle_property, int max_range);
void printBattleProperty(BattleProperty *battle_property);

#endif