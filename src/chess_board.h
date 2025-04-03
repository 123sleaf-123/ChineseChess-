#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "global.h"
#include "chess.h"
#include "chess_record.h"
#include "chess_stack.h"
#include "chess_board_block.h"

struct Tips {
    char strs[8][64];
    int top;
};

typedef struct ChessBoard
{
    struct Chess ***block;
    struct BoardBlock ***boardBlock;
    struct ChessStack *objects;
    char **moveablePos;
    char **attackablePos;
    PLAYER user;
    struct Chess *chessChoose;
    struct Chess *chessTobeOperated;
    struct ChessStack **dead_chess;
    struct Tips *tip;
    RecordStack *record;
} *Board;

char **initMatrix();
void freeMatrix(char **matrix);
struct ChessBoard* initChessBoard();
bool setChessBoardBlock(struct ChessBoard *board, int row, int col, struct Chess *chess);
void reset_moveablePos(struct ChessBoard *board);
void resetAttackablePos(struct ChessBoard *board);
int setChessBoardMoveablePos(struct ChessBoard *board, int row, int col, int val);
bool placeChess(struct ChessBoard *board, int row, int col, struct Chess *chess);
struct Chess *getChessByPos(struct ChessBoard *board, int row, int col);
RecordStack *getRecordStack(struct ChessBoard *board);
struct Chess *getChessChoose(struct ChessBoard *board);
void setChessChoose(struct ChessBoard *board, struct Chess *chess);
struct Chess *getChessTobeOperated(struct ChessBoard *board);
void setChessTobeOperated(struct ChessBoard *board, struct Chess *chess);
int getBlockMovementCost(struct ChessBoard *board, int row, int col);
void aiLogic(struct ChessBoard *board, int *dest_row, int *dest_col);

#endif