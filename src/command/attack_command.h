#ifndef ATTACKCommand_H
#define ATTACKCommand_H

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


void attackCommandExecute(Command* cmd);
void attackCommandUndo(Command *cmd);
Command* createAttackCommand(struct Chess * attacker, struct Chess * target, int damage);

#endif // ATTACKCommand_H