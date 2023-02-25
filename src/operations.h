#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "chess_board.h"

void actionFinished(struct ChessBoard *board);
int isInside(int row, int col); 
int isNull(struct ChessBoard* board, int row, int col);
int isControllable(struct ChessBoard* board, int row, int col);
int friendlyFireDetect(struct ChessBoard* board, int row, int col);
int isBeyond(struct ChessBoard* board, int row, int col);

int choose(struct ChessBoard* board, int src_row, int src_col);
void moveablePosition(struct ChessBoard* board, int src_row, int src_col);
int isMoveable(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col);
int action(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col);
int isGameEnd(struct ChessBoard* board);
int autoColor_printf(int user, const char *format, ...);
int color_printf(int text_color, const char *format, ...);
void printChessBoard(struct ChessBoard* board);

#endif