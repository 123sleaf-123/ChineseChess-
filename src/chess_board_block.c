#include "chess_board_block.h"

// 棋盘格子初始化函数（新增）
struct BoardBlock* initBoardBlock(TerrainType terrain, int elevation) {
    struct BoardBlock* block = malloc(sizeof(struct BoardBlock));
    block->chess = NULL;
    block->terrain = terrain;
    block->elevation = elevation;    
    return block;
}

struct BoardBlock* initDefaultBoardBlock() {
    return initBoardBlock(TERRAIN_PLAIN, 0);
}

// 棋盘格子释放函数（新增）
void freeBoardBlock(struct BoardBlock* block) {
    free(block);
}

float getTerrainCost(TerrainType terrain) {
    switch (terrain) {
        case TERRAIN_PLAIN:
            return 1.0f;
        case TERRAIN_MOUNTAIN:
            return 100.0f;
        case TERRAIN_FOREST:
            return 2.0f;
        case TERRAIN_RIVER:
            return 2.0f;
        default:
            return 1.0;
    }
}

float getTerrainCostByBlock(struct BoardBlock* block) {
    TerrainType terrain = block->terrain;
    return getTerrainCost(terrain);
}