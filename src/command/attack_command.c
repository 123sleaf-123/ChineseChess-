#include "attack_command.h"

// 攻击执行函数
void attackCommandExecute(Command* cmd) {
    AttackCommand* ac = (AttackCommand*)cmd;
    ac->target_prev_health = getChessHealth(ac->target);
    takeDamageChess(ac->target, ac->damage);
    ac->target->is_alive = getChessHealth(ac->target) > 0;

    // 如果目标死亡，从棋盘上移除
    if (!ac->target->is_alive) {
        removeChessfromBoard(ac->base.board, ac->target);
        // 将死亡棋子放入死亡栈
        pushDeadChess2Stack(ac->base.board, ac->target);
    }
}

// 攻击撤销函数
void attackCommandUndo(Command* cmd) {
    AttackCommand* ac = (AttackCommand*)cmd;
    recoverChess(ac->target, ac->target_prev_health);
}

// 创建攻击命令
Command* createAttackCommand(struct Chess * attacker, struct Chess * target, int damage) {
    AttackCommand* cmd = malloc(sizeof(AttackCommand));
    cmd->base.type = ATTACK;
    cmd->base.execute = attackCommandExecute;
    cmd->base.undo = attackCommandUndo;
    cmd->base.next = NULL;
    cmd->attacker = attacker;
    cmd->target = target;
    cmd->damage = damage;
    return (Command*)cmd;
}