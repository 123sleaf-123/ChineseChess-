#ifndef HEAL_COMMAND_H
#define HEAL_COMMAND_H

#include "chess.h"
#include "command.h"
typedef struct {
    Command base;
    struct Chess *healer;
    struct Chess *target;
    int heal_amount;
    int target_prev_health;
} HealCommand;

void HealCommand_execute(Command *cmd);
void HealCommand_undo(Command *cmd);
Command *create_heal_command(struct Chess *healer, struct Chess *target, int heal_amount);

#endif // HEAL_COMMAND_H