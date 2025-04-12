#include "heal_command.h"

// 治疗执行函数
void HealCommand_execute(Command* cmd) {
    HealCommand* hc = (HealCommand*)cmd;
    hc->target_prev_health = getChessHealth(hc->target);
    recoverChess(hc->target, hc->heal_amount);
}

// 治疗撤销函数
void HealCommand_undo(Command* cmd) {
    HealCommand *hc = (HealCommand *)cmd;
    // 撤销治疗，恢复到之前的生命值
    setChessHealth(hc->target, hc->target_prev_health);
}


// 创建治疗命令
Command* create_heal_command(struct Chess * healer, struct Chess * target, int heal_amount) {
    HealCommand* cmd = malloc(sizeof(HealCommand));
    cmd->base.type = HEAL;
    cmd->base.execute = HealCommand_execute;
    cmd->base.undo = HealCommand_undo;
    cmd->base.next = NULL;
    cmd->healer = healer;
    cmd->target = target;
    cmd->heal_amount = heal_amount;
    return (Command*)cmd;
}