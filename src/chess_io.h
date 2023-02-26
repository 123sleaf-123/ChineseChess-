#ifndef CHESS_IO_H
#define CHESS_IO_H

#include "chess_board.h"

int autoColor_printf(int user, const char *format, ...);
int color_printf(int text_color, const char *format, ...);
void printChessBoard(struct ChessBoard* board);

#endif