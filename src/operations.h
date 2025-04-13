#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "chess_board.h"

int choose(struct ChessBoard* board, int src_row, int src_col);
int moveChess(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col);
bool withdraw(struct ChessBoard *board);
int fight(struct ChessBoard* board, ChessPtr attacker, ChessPtr defender);
int fightByPos(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col);

#endif