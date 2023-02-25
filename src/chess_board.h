#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "chess.h"
#include "chess_stack.h"

typedef struct ChessBoard
{
    struct Chess *block[10][9];
    struct ChessStack *objects;
    char moveablePos[10][9];
    int user;
    struct Chess *chessChoose;
    struct ChessStack *dead_player1;
    struct ChessStack *dead_player2;
} *Board;

struct ChessBoard* initChessBoard();
int setChessBoardMoveablePos(struct ChessBoard *board, int row, int col, int val);

#endif