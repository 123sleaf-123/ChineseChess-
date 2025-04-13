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

void healCommandExecute(Command *cmd);
void healCommandUndo(Command *cmd);
void healCommandFree(Command *cmd);
Command *createHealCommand(struct Chess *healer, struct Chess *target, int heal_amount);

#endif // HEAL_COMMAND_H