#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "global.h"
#include "chess.h"
#include "chess_stack.h"

struct Tips {
    char strs[8][64];
    int top;
};

struct RecordStack {
    int **commands;
    int top;
};

typedef enum {
    TERRAIN_PLAIN,      // 平原
    TERRAIN_MOUNTAIN,   // 山脉
    TERRAIN_FOREST,     // 森林
    TERRAIN_RIVER,      // 河流
    // 可根据需要添加更多地形
} TerrainType;

// 棋盘格子结构体（新增）
struct BoardBlock {
    struct Chess* chess;    // 棋子指针
    TerrainType terrain;    // 地形类型
    int elevation;          // 高度值
};

typedef struct ChessBoard
{
    struct Chess ***block;
    struct BoardBlock ***boardBlock;
    struct ChessStack *objects;
    char **moveablePos;
    PLAYER user;
    struct Chess *chessChoose;
    struct ChessStack **dead_chess;
    struct Tips *tip;
    struct RecordStack record;
} *Board;

char **initMatrix();
void freeMatrix(char **matrix);
struct ChessBoard* initChessBoard();
bool setChessBoardBlock(struct ChessBoard *board, int row, int col, struct Chess *chess);
void reset_moveablePos(struct ChessBoard *board);
int setChessBoardMoveablePos(struct ChessBoard *board, int row, int col, int val);
bool placeChess(struct ChessBoard *board, int row, int col, struct Chess *chess);
void aiLogic(struct ChessBoard *board, int *dest_row, int *dest_col);

#endif