#ifndef CHESS_LOGIC_H
#define CHESS_LOGIC_H

#include "chess_board.h"
#include "chess.h"

bool isInside(int row, int col); 
bool isNull(struct ChessBoard* board, int row, int col);
bool isControllable(struct ChessBoard* board, int row, int col);
bool friendlyFireDetect(struct ChessBoard* board, int row, int col);
bool isBeyond(struct ChessBoard* board, int row, int col);
bool isInsidePalace(struct ChessBoard *board, int row, int col);
bool isMoveable(struct ChessBoard* board, int dest_row, int dest_col);
bool isGameEnd(struct ChessBoard* board);
void pathFindingByPos(struct ChessBoard *board, int src_row, int src_col);
void pathFindingByChess(struct ChessBoard *board, struct Chess* chess);
void moveablePosition(struct ChessBoard* board, int src_row, int src_col);
void actionFinished(struct ChessBoard *board);

#endif