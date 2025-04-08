#ifndef PROPERTY_BASIC_H
#define PROPERTY_BASIC_H

#include "global.h"

typedef struct {
    int strength;      // 力量
    int magic;         // 魔力
    int skill;         // 技巧
    int speed;         // 速度
    int luck;          // 幸运
    int defense;       // 防守
    int magic_defense;  // 魔防
    int charm;         // 魅力
    int movement;      // 移动力
    int health;        // 生命值
    int level;         // 等级
    int experience;    // 经验值
    int attack_range;  // 攻击范围
} BasicProperty;

void initBasicProperty(BasicProperty *property, int strength, int magic, int skill, int speed, int luck, int defense, int magic_defense, int charm, int movement, int health, int level, int experience, int attack_range);
BasicProperty *createBasicPropertyDeault();

void addBasicProperty(BasicProperty *target, BasicProperty *source);
void removeBasicProperty(BasicProperty *target, BasicProperty *source);

#endif