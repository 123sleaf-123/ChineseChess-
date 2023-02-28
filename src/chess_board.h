#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "global.h"
#include "chess.h"
#include "chess_stack.h"

struct Tips {
    char strs[8][64];
    int top;
};

typedef struct ChessBoard
{
    struct Chess *block[10][9];
    struct ChessStack *objects;
    char moveablePos[10][9];
    PLAYER user;
    struct Chess *chessChoose;
    struct ChessStack *dead_player1;
    struct ChessStack *dead_player2;
    struct Tips *tip;
} *Board;

struct ChessBoard* initChessBoard();
bool setChessBoardBlock(struct ChessBoard *board, int row, int col, struct Chess *chess);
int setChessBoardMoveablePos(struct ChessBoard *board, int row, int col, int val);

#endif