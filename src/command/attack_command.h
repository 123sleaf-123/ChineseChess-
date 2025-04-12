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
    int target_was_alive;
} AttackCommand;

// 攻击执行函数
void AttackCommand_execute(Command* cmd) {
    AttackCommand* ac = (AttackCommand*)cmd;
    ac->target_prev_health = getChessHealth(ac->target);
    takeDamageChess(ac->target, ac->damage);
    ac->target_was_alive = getChessHealth(ac->target) > 0;
    ac->target->is_alive = ac->target_was_alive;

    // 如果目标死亡，从棋盘上移除
    if (!ac->target_was_alive) {
        removeChessfromBoard(ac->base.board, ac->target);
        // 将死亡棋子放入死亡栈
        pushDeadChess2Stack(ac->base.board, ac->target);
    }
}

// 攻击撤销函数
void AttackCommand_undo(Command* cmd) {
    AttackCommand* ac = (AttackCommand*)cmd;
    recoverChess(ac->target, ac->target_prev_health);
}

// 创建攻击命令
Command* create_attack_command(struct Chess * attacker, struct Chess * target, int damage) {
    AttackCommand* cmd = malloc(sizeof(AttackCommand));
    cmd->base.type = ATTACK;
    cmd->base.execute = AttackCommand_execute;
    cmd->base.undo = AttackCommand_undo;
    cmd->base.next = NULL;
    cmd->attacker = attacker;
    cmd->target = target;
    cmd->damage = damage;
    return (Command*)cmd;
}

#endif // ATTACK_COMMAND_H