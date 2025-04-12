#ifndef ATTACK_COMMAND_H
#define ATTACK_COMMAND_H

#include "command.h"
#include "chess_board.h"
#include "chess.h"

// 攻击命令子类
typedef struct {
    Command base;      // 继承基类
    struct Chess *attacker;
    struct Chess *target;
    int damage;
    int target_prev_health;
} AttackCommand;


void AttackCommand_execute(Command* cmd);
void AttackCommand_undo(Command *cmd);
Command* create_attack_command(struct Chess * attacker, struct Chess * target, int damage);

#endif // ATTACK_COMMAND_H