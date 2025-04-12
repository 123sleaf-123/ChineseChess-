#include "heal_command.h"

// 治疗执行函数
void healCommandExecute(Command* cmd) {
    HealCommand* hc = (HealCommand*)cmd;
    hc->target_prev_health = getChessHealth(hc->target);
    recoverChess(hc->target, hc->heal_amount);
}

// 治疗撤销函数
void healCommandUndo(Command* cmd) {
    HealCommand *hc = (HealCommand *)cmd;
    // 撤销治疗，恢复到之前的生命值
    setChessHealth(hc->target, hc->target_prev_health);
}


// 创建治疗命令
Command* createHealCommand(struct Chess * healer, struct Chess * target, int heal_amount) {
    HealCommand* cmd = malloc(sizeof(HealCommand));
    cmd->base.type = HEAL;
    cmd->base.execute = healCommandExecute;
    cmd->base.undo = healCommandUndo;
    cmd->base.next = NULL;
    cmd->healer = healer;
    cmd->target = target;
    cmd->heal_amount = heal_amount;
    return (Command*)cmd;
}