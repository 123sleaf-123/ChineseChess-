#ifndef CHESS_BOARD_BLOCK_H
#define CHESS_BOARD_BLOCK_H

#include "chess.h"
#include "global.h"

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

struct BoardBlock* initBoardBlock(TerrainType terrain, int elevation);
struct BoardBlock* initDefaultBoardBlock();
void freeBoardBlock(struct BoardBlock* block);

#endif