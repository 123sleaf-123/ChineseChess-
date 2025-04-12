#include "move_command.h"
#include "operations.h"

void MoveCommandExecute(Command *cmd) {
    MoveCommand *move_cmd = (MoveCommand *)cmd;
    struct ChessBoard *board = move_cmd->base.board;

    // 执行移动操作
    moveChess(board, move_cmd->src_row, move_cmd->src_col, move_cmd->dest_row, move_cmd->dest_col);
}

void MoveCommandUndo(Command *cmd) {
    MoveCommand *move_cmd = (MoveCommand *)cmd;
    struct ChessBoard *board = move_cmd->base.board;

    // 撤销移动操作
    moveChess(board, move_cmd->dest_row, move_cmd->dest_col, move_cmd->src_row, move_cmd->src_col);
}

Command *createMoveCommand(struct Chess *chess, int src_row, int src_col, int dest_row, int dest_col) {
    MoveCommand *cmd = (MoveCommand *)malloc(sizeof(MoveCommand));
    cmd->base.type = MOVE;
    cmd->base.execute = MoveCommandExecute;
    cmd->base.undo = MoveCommandUndo;
    cmd->chess = chess;
    cmd->src_row = src_row;
    cmd->src_col = src_col;
    cmd->dest_row = dest_row;
    cmd->dest_col = dest_col;

    return (Command *)cmd;
}