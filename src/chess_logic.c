#include "chess.h"
#include "chess_board.h"
#include "global.h"


/**
 * @brief 是否超出棋盘范围
 *
 * @param row 目标行
 * @param col 目标列
 * @return bool 返回false，若目标位置超出棋盘；否则，返回true
 */
bool isInside(int row, int col) {
    return (row < BOARD_ROW) && (col < BOARD_COL) && (row >= 0) && (col >= 0);
}

/**
 * @brief 当前坐标位置是否存在棋子
 *
 * @param board 棋盘
 * @param row 行
 * @param col 列
 * @return bool 返回true，若不存在棋子；返回false，若存在棋子
 */
bool isEmptyBlock(struct ChessBoard *board, int row, int col) {
    return board->block[row][col] == NULL;
}

/**
 * @brief 原位置是否存在己方棋子
 *
 * @param board 棋盘
 * @param row 原行
 * @param col 原列
 * @return bool 返回true，若存在己方棋子；返回false，若不存在棋子或存在敌方棋子
 */
bool isControllable(struct ChessBoard *board, int row, int col) {
    return !isEmptyBlock(board, row, col) && (board->block[row][col]->owner == board->user);
}

/**
 * @brief 目标位置是否存在己方棋子，是否会造成友伤
 *
 * @param board 棋盘
 * @param row 目标行
 * @param col 目标列
 * @return bool 返回true，若目标位置为我方棋子；返回false，若目标位置为空或敌方棋子
 */
bool friendlyFireDetect(struct ChessBoard *board, int row, int col) {
    return !isEmptyBlock(board, row, col) && (board->block[row][col]->owner == board->user);
}

/**
 * @brief 目标位置是否存在敌方棋子
 *
 * @param board 棋盘
 * @param row 目标行
 * @param col 目标列
 * @return bool 返回true，若目标位置为敌方棋子；返回false，若目标位置为空或己方棋子
 */
bool hasEnemy(struct ChessBoard *board, int row, int col) {
    return !isEmptyBlock(board, row, col) && (board->block[row][col]->owner != board->user);
}

/**
 * @brief 位置是否在玩家领地内；玩家一的领地是5-9行，玩家二的领地是0-4行
 * 使用前最好先使用isInside()
 *
 * @param board 棋盘
 * @param row
 * @param col
 * @return bool 返回true，若玩家不在自己的领地内；否则返回false
 */
bool isBeyond(struct ChessBoard *board, int row, int col) {
    if (board->user == PLAYER_1)
        return !((5 <= row && row <= 9) && (0 <= col && col <= 8));
    if (board->user == PLAYER_2)
        return !((0 <= row && row <= 4) && (0 <= col && col <= 8));
    return true;
}

bool isInsidePalace(struct ChessBoard *board, int row, int col) {
    if (board->user == PLAYER_1)
        return (7 <= row) && (row <= 9) && (3 <= col) && (col <= 5);
    if (board->user == PLAYER_2)
        return (0 <= row) && (row <= 2) && (3 <= col) && (col <= 5);
    return true;
}

bool setBoolMatrix(char **matrix, int row, int col, char value) {
    if ((0 <= row && row <= 9) && (0 <= col && col <= 8)) {
        matrix[row][col] = value;
        return true;
    } else
        return false;
}

bool isMoveable(struct ChessBoard *board, int dest_row, int dest_col) {
    if (board->moveablePos == NULL) {
        return false;
    }
    return board->moveablePos[dest_row][dest_col] == true;
}

bool isAttackable(struct ChessBoard *board, int dest_row, int dest_col) {
    if (board->attackablePos == NULL) {
        return false;
    }
    return board->attackablePos[dest_row][dest_col] == true;
}

/**
 * @brief 判断游戏是否结束（是否将死）
 *
 * @param board 棋盘
 * @return bool 返回true，如果已经将死；否则返回false
 */
bool isGameEnd(struct ChessBoard *board) {
    for (int i = 0; i < 2; i++) {
        if ((isChessStackEmpty(board->dead_chess[i]) == false) &&
            (chessStackTop(board->dead_chess[i])->type == GENERAL)) {
            return true;
        }
    }
    return false;
    // if (
    // (isChessStackEmpty(board->dead_player1) == false && chessStackTop(board->dead_player1)->type == GENERAL) ||
    // (isChessStackEmpty(board->dead_player2) == false && chessStackTop(board->dead_player2)->type == GENERAL))
    //     return true;
    // else return false;
}

void dfs(struct ChessBoard *board, char ***matrix, int row, int col, int movement_left) {
    if (!isInside(row, col) || movement_left < 0 || hasEnemy(board, row, col)) {
        return;
    }

    bool ally_flag = friendlyFireDetect(board, row, col);

    // DFS in four directions
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int new_row = row + dx[i];
        int new_col = col + dy[i];
        // Continue DFS only if not blocked by enemy
        if (!(!isEmptyBlock(board, row, col) && board->block[row][col]->owner != board->user)) {
            dfs(board, matrix, new_row, new_col, movement_left - getBlockMovementCost(board, row, col));
        }
    }

    if (!ally_flag)
        setBoolMatrix(*matrix, row, col, true);
}

void moveablePosFindingByChess(struct ChessBoard *board, struct Chess *chess, char **matrix) {
    if (matrix == NULL) {
        matrix = initMatrix();
    }
    int src_row = getChessPosition(chess)->x;
    int src_col = getChessPosition(chess)->y;
    int movement = getChessMovement(chess);
    dfs(board, &matrix, src_row, src_col, movement);
}

void moveablePosFindingByPos(struct ChessBoard *board, int src_row, int src_col, char **matrix) {
    struct Chess *chess = board->block[src_row][src_col];
    return moveablePosFindingByChess(board, chess, matrix);
}

void moveablePosition(struct ChessBoard *board, int src_row, int src_col) {
    resetMoveablePos(board);
    moveablePosFindingByPos(board, src_row, src_col, board->moveablePos);
}

void attackableAreaFindingByChess(struct ChessBoard *board, struct Chess *chess, char **matrix) {
    if (matrix == NULL) {
        matrix = initMatrix();
    }
    int src_row = getChessPosition(chess)->x;
    int src_col = getChessPosition(chess)->y;
    int attack_range_min = getChessMinRange(chess);
    int attack_range_max = getChessMaxRange(chess);

    // 遍历所有可能的 Δx（从 -attack_range 到 +attack_range）
    for (int attack_range = attack_range_min; attack_range <= attack_range_max; attack_range++) {
        // 遍历所有可能的 Δx（从 -attack_range 到 +attack_range）
        for (int dx = -attack_range; dx <= attack_range; dx++) {
            // 计算对应的 |Δy| = attack_range - |dx|
            int dy_abs = attack_range - abs(dx);

            // 检查 Δy 是否有效（避免重复计算）
            if (dy_abs < 0)
                continue;

            // 两种情况：Δy = +dy_abs 或 Δy = -dy_abs
            for (int sign = -1; sign <= 1; sign += 2) {
                int dy = sign * dy_abs;
                int new_row = src_row + dx;
                int new_col = src_col + dy;

                // 检查边界
                if (isInside(new_row, new_col)) {
                    matrix[new_row][new_col] = true;
                }
            }
        }
    }
}

void attackableAreaFindingByPos(struct ChessBoard *board, int src_row, int src_col, char **matrix) {
    attackableAreaFindingByChess(board, getChessByPos(board, src_row, src_col), matrix);
}

/**
 * @brief 计算攻击范围
 *
 * @param board 棋盘
 * @param src_row 原行
 * @param src_col 原列
 */
void attackablePosition(struct ChessBoard *board, int src_row, int src_col) {
    resetAttackablePos(board);
    attackableAreaFindingByPos(board, src_row, src_col, board->attackablePos);
}

/**
 * @brief 行动完成，可移动路径图层和已选择棋子清空
 *
 * @param board 棋盘
 */
void actionFinished(struct ChessBoard *board) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 9; j++) {
            board->moveablePos[i][j] = false;
            board->attackablePos[i][j] = false;
        }
    }
    board->chess_choose = NULL;
}

void aiLogic(struct ChessBoard *board, int *dest_row, int *dest_col) {
    ChessPtr chess;
    for (int i = 0; i <= board->objects->top; i++) {
        if (board->objects->stack[i]->owner != board->user) {
            chess = board->objects->stack[i];
            // moveablePosFindingByChess(board, chess,);
            break;
        }
    }
    for (int i = 0; i < BOARD_ROW; i++) {
        for (int j = 0; j < BOARD_COL; j++) {
            if (!isEmptyBlock(board, i, j) && (board->block[i][j]->owner != board->user)) // 非空且为敌人
            {
            }
        }
    }
}