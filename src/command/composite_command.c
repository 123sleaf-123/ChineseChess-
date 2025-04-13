#include "composite_command.h"


void compositeCommandExecute(Command* cmd) {
    CompositeCommand* cc = (CompositeCommand*)cmd;
    for (int i = 0; i < cc->count; i++) {
        cc->sub_commands[i]->execute(cc->sub_commands[i]);
    }
}

void compositeCommandUndo(Command* cmd) {
    CompositeCommand* cc = (CompositeCommand*)cmd;
    for (int i = cc->count - 1; i >= 0; i--) { // 逆序撤销
        cc->sub_commands[i]->undo(cc->sub_commands[i]);
    }
}

void compositeCommandFree(Command* cmd) {
    CompositeCommand* cc = (CompositeCommand*)cmd;
    for (int i = 0; i < cc->count; i++) {
        cc->sub_commands[i]->free(cc->sub_commands[i]); // 释放子命令
    }
    free(cc); // 释放复合命令
}

void* createCompositeCommand(CompositeCommand* composite_cmd, Command** sub_commands, int count) {
    composite_cmd->base.execute = compositeCommandExecute;
    composite_cmd->base.undo = compositeCommandUndo;
    composite_cmd->sub_commands = sub_commands;
    composite_cmd->count = count;
    return composite_cmd;
}