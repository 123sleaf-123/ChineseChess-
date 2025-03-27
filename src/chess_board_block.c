#include "chess_board_block.h"

// 棋盘格子初始化函数（新增）
struct BoardBlock* initBoardBlock(TerrainType terrain, int elevation) {
    struct BoardBlock* block = malloc(sizeof(struct BoardBlock));
    block->chess = NULL;
    block->terrain = terrain;
    block->elevation = elevation;
    
    // 根据地形设置移动消耗
    switch(terrain) {
        case TERRAIN_PLAIN:
            block->moveCost = 1;
            break;
        case TERRAIN_MOUNTAIN:
            block->moveCost = 3;
            break;
        case TERRAIN_FOREST:
            block->moveCost = 2;
            break;
        case TERRAIN_RIVER:
            block->moveCost = 2;
            break;
        default:
            block->moveCost = 1;
    }
    
    return block;
}

struct BoardBlock* initDefaultBoardBlock() {
    return initBoardBlock(TERRAIN_PLAIN, 0);
}

// 棋盘格子释放函数（新增）
void freeBoardBlock(struct BoardBlock* block) {
    free(block);
}