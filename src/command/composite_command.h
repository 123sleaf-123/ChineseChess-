#ifndef COMPOSITE_COMMAND_H
#define COMPOSITE_COMMAND_H

#include "command.h"

// 复合命令结构
typedef struct {
    Command base;
    Command** sub_commands; // 子命令数组
    int count;
} CompositeCommand;

void compositeCommandExecute(Command *cmd);
void compositeCommandUndo(Command *cmd);
void* createCompositeCommand(CompositeCommand* composite_cmd, Command** sub_commands, int count);

#endif // COMPOSITE_COMMAND_H