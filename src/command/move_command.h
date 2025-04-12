#ifndef MOVECommand_H
#define MOVECommand_H

#include "command.h"

typedef struct {
    Command base;      // 继承基类
    struct Chess *chess;
    int src_row;
    int src_col;
    int dest_row;
    int dest_col;
} MoveCommand;

void moveCommandExecute(Command *cmd);
void moveCommandUndo(Command *cmd);
Command *createMoveCommand(struct Chess *chess, int src_row, int src_col, int dest_row, int dest_col);

#endif