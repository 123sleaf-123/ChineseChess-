#include "global.h"
#include "operations.h"
#include "tools.h"

/*
    1.不可移动：
        1.1. 原位置不存在己方棋子或不存在棋子
        1.2. 目标位置超出棋盘范围
        1.3. 目标位置存在己方棋子
        1.4. 不符合棋子移动规则
    2. 可移动：操纵了己方棋子，未超出棋盘范围，且符合移动规则，且目标位置不存在己方棋子
        2.1. 击杀
        2.2. 无击杀
*/

/**
 * @brief 是否超出棋盘范围
 * 
 * @param row 目标行
 * @param col 目标列
 * @return int 返回false，若目标位置超出棋盘；否则，返回true
 */
int isInside(int row, int col) {
    return (row < BOARD_ROW) && (col < BOARD_COL) && (row >= 0) && (col >= 0);
}

/**
 * @brief 当前坐标位置是否存在棋子
 * 
 * @param board 棋盘
 * @param row 行
 * @param col 列
 * @return int 返回true，若不存在棋子；返回false，若存在棋子
 */
int isNull(struct ChessBoard* board, int row, int col) {
    return board->block[row][col] == NULL;
}

/**
 * @brief 原位置是否存在己方棋子
 * 
 * @param board 棋盘
 * @param row 原行
 * @param col 原列
 * @return int 返回true，若存在己方棋子；返回false，若不存在棋子或存在敌方棋子
 */
int isControllable(struct ChessBoard* board, int row, int col) {
    return !isNull(board, row, col) && (board->block[row][col]->owner == board->user);
}

/**
 * @brief 目标位置是否存在己方棋子，是否会造成友伤
 * 
 * @param board 棋盘
 * @param row 目标行
 * @param col 目标列
 * @return int 返回true，若目标位置为我方棋子；返回false，若目标位置为空或敌方棋子
 */
int friendlyFireDetect(struct ChessBoard* board, int row, int col) {
    return !isNull(board, row, col) 
    && (board->block[row][col]->owner == board->user);
}

/**
 * @brief 位置是否在玩家领地内；玩家一的领地是5-9行，玩家二的领地是0-4行
 * 使用前最好先使用isInside()
 * 
 * @param board 棋盘
 * @param row 
 * @param col 
 * @return int 返回true，若玩家不在自己的领地内；否则返回false
 */
int isBeyond(struct ChessBoard* board, int row, int col) {
    if (board->user == PLAYER_1) 
        return !((5 <= row && row <= 9) && (0 <= col && col <= 8));
    if (board->user == PLAYER_2) 
        return !((0 <= row && row <= 4) && (0 <= col && col <= 8));
    return true;
}

int isInsidePalace(struct ChessBoard* board, int row, int col) {
    if (board->user == PLAYER_1) 
        return (7 <= row) && (row <= 9) && (3 <= col) && (col <= 5);
    if (board->user == PLAYER_2) 
        return (0 <= row) && (row <= 2) && (3 <= col) && (col <= 5);
    return true;
}

/**
 * @brief 行动完成，可移动路径图层和已选择棋子清空
 * 
 * @param board 棋盘
 */
void actionFinished(struct ChessBoard *board) {
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board->moveablePos[i][j] = false;
        } 
    }
    board->chessChoose = NULL;
}

/**
 * @brief 选择棋子，若可以操纵，则记录当前选中棋子，计算出可移动路径图层
 * 
 * @param board 棋盘
 * @param src_row 
 * @param src_col 
 * @return int 返回true，若棋子可以操纵；否则，返回false
 */
int choose(struct ChessBoard* board, int src_row, int src_col) {
    if (isControllable(board, src_row, src_col) == false) 
        return false;
    else {
        board->chessChoose = board->block[src_row][src_col];
        moveablePosition(board, src_row, src_col); 
        return true;
    }
}

void moveablePosition(struct ChessBoard* board, int src_row, int src_col) {
    struct Chess* chess = board->block[src_row][src_col];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board->moveablePos[i][j] = false;
        } 
    }
    
    switch (chess->type) {
        case GENERAL: // 是否在九宫格内且移动了一格
        {
            int dest_row[4], dest_col[4];
            dest_row[0] = src_row + 1;
            dest_row[1] = src_row;
            dest_row[2] = src_row - 1;
            dest_row[3] = src_row;
            dest_col[0] = src_col;
            dest_col[1] = src_col + 1;
            dest_col[2] = src_col;
            dest_col[3] = src_col - 1;
            for (int i = 0; i < 4; i++)
            {
                if (isInsidePalace(board, dest_row[i], dest_col[i]) == true) 
                    board->moveablePos[dest_row[i]][dest_col[i]] = true;
            }
            break;
        }
        case CHARIOT: // 车，目标位置与源位置是否在同一行或同一列
        {
            for (int i = src_row+1, j = src_col; isInside(i, j); ++i) {
                board->moveablePos[i][j] = true;
                if (isNull(board, i, j) == false) break;
            }
            for (int i = src_row-1, j = src_col; isInside(i, j); --i) {
                board->moveablePos[i][j] = true;
                if (isNull(board, i, j) == false) break;
            }
            for (int i = src_row, j = src_col+1; isInside(i, j); ++j) {
                board->moveablePos[i][j] = true;
                if (isNull(board, i, j) == false) break;
            }
            for (int i = src_row, j = src_col-1; isInside(i, j); --j) {
                board->moveablePos[i][j] = true;
                if (isNull(board, i, j) == false) break;
            }
            break;
        }
        case HORSE: // 马
        {
            int dest_row[4], dest_col[4];
            dest_row[0] = src_row + 1;
            dest_row[1] = src_row;
            dest_row[2] = src_row - 1;
            dest_row[3] = src_row;
            dest_col[0] = src_col;
            dest_col[1] = src_col + 1;
            dest_col[2] = src_col;
            dest_col[3] = src_col - 1;
            for (int i = 0; i < 4; i++)
            {
                if (isInside(dest_row[i], dest_col[i]) && isNull(board, dest_row[i], dest_col[i])) {
                    if (i == 0) {
                        // 下
                        setChessBoardMoveablePos(board, dest_row[i] + 1, dest_col[i] - 1, true);
                        setChessBoardMoveablePos(board, dest_row[i] + 1, dest_col[i] + 1, true);
                    }
                    if (i == 1) {
                        // 右
                        setChessBoardMoveablePos(board, dest_row[i] + 1, dest_col[i] + 1, true);
                        setChessBoardMoveablePos(board, dest_row[i] - 1, dest_col[i] + 1, true);
                    }
                    if (i == 2) {
                        // 上
                        setChessBoardMoveablePos(board, dest_row[i] - 1, dest_col[i] + 1, true);
                        setChessBoardMoveablePos(board, dest_row[i] - 1, dest_col[i] - 1, true);
                    }
                    if (i == 3) {
                        // 左
                        setChessBoardMoveablePos(board, dest_row[i] + 1, dest_col[i] - 1, true);
                        setChessBoardMoveablePos(board, dest_row[i] - 1, dest_col[i] - 1, true);
                    }
                }
            }
            
            break;
        }
        case ARTILLERY: 
            // 目标位置与源位置是否在同一行或同一列
            // 且目标位置有敌人，目标位置与源位置之间是否有棋子
        {
            int i, j;
            for (i = src_row+1, j = src_col; isInside(i, j) && isNull(board, i, j); ++i) {
                board->moveablePos[i][j] = true;
            }
            for (++i; isInside(i, j); ++i) {
                if (!isNull(board, i, j)) {
                    if (!friendlyFireDetect(board, i, j)) board->moveablePos[i][j] = true;
                    break;
                }
            }
            for (i = src_row-1, j = src_col; isInside(i, j) && isNull(board, i, j); --i) {
                board->moveablePos[i][j] = true;
            }
            for (--i; isInside(i, j); --i) {
                if (!isNull(board, i, j)) {
                    if (!friendlyFireDetect(board, i, j)) board->moveablePos[i][j] = true;
                    break;
                }
            }
            for (i = src_row, j = src_col+1; isInside(i, j) && isNull(board, i, j); ++j) {
                board->moveablePos[i][j] = true;
            }
            for (++j; isInside(i, j); ++j) {
                if (!isNull(board, i, j)) {
                    if (!friendlyFireDetect(board, i, j)) board->moveablePos[i][j] = true;
                    break;
                }
            }
            for (i = src_row, j = src_col-1; isInside(i, j) && isNull(board, i, j); --j) {
                board->moveablePos[i][j] = true;
            }
            for (--j; isInside(i, j); --j) {
                if (!isNull(board, i, j)) {
                    if (!friendlyFireDetect(board, i, j)) board->moveablePos[i][j] = true;
                    break;
                }
            }
            break;
        }
        case ELEPHANT: 
        {
            // 在内部且路径上没有敌人
            char stop[4] = {false, false, false, false};
            for (int i = 1; i <= 2; i++)
            {
                // 右下角，左下角，左上角，右上角
                int 
                dest_row[4] = { src_row + i, src_row + i, src_row - i, src_row - i }, 
                dest_col[4] = { src_col + i, src_col - i, src_col - i, src_col + i }; 
                for (int j = 0; j < 4; j++)
                {
                    // 如果位置不在棋盘内、越界或者有棋子阻挡象眼，则停止前进预测
                    // 否则就认为可前进
                    if (i == 1 && (isBeyond(board, dest_row[j], dest_col[j]) || !isNull(board, dest_row[j], dest_col[j]))) 
                        stop[j] = true;
                    if (i == 2 && stop[j] == false) {
                        setChessBoardMoveablePos(board, dest_row[j], dest_col[j], true);
                    }
                }
            }
            break;
        }
        case WARRIOR:
        {
            // 右下角，左下角，左上角，右上角
            int 
            dest_row[4] = { src_row + 1, src_row + 1, src_row - 1, src_row - 1 }, 
            dest_col[4] = { src_col + 1, src_col - 1, src_col - 1, src_col + 1 }; 
            for (int i = 0; i < 4; i++)
            {
                if (isInsidePalace(board, dest_row[i], dest_col[i])) {
                    setChessBoardMoveablePos(board, dest_row[i], dest_col[i], true);
                }
            }
            break;
        }
        case SOLDIER:
        {
            if (isInside(src_row, src_col) && isBeyond(board, src_row, src_col)) {
                // 越过领地（楚河汉界），可以向右左走
                setChessBoardMoveablePos(board, src_row, src_col + 1, true);
                setChessBoardMoveablePos(board, src_row, src_col - 1, true);
            }
            // 无论何时都可以向前走（当前也没法向后走了
            if (board->user == PLAYER_1) 
                setChessBoardMoveablePos(board, src_row - 1, src_col, true);
            if (board->user == PLAYER_2) 
                setChessBoardMoveablePos(board, src_row + 1, src_col, true);
            break;
        }
    }
}

// 是否符合棋子移动规则
int isMoveable(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col) {
    return board->moveablePos[dest_row][dest_col] == true;
}

int action(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col) {
    // if (isControllable(board, src_row, src_col)) {
    if (isInside(dest_row, dest_col)) {
        if (!friendlyFireDetect(board, dest_row, dest_col)) {
            if (isMoveable(board, src_row, src_col, dest_row, dest_col)) {
                if (!isNull(board, dest_row, dest_col) 
                && board->block[dest_row][dest_col]->owner != board->user) {
                    struct ChessStack *cstk;
                    struct Chess *dead = board->block[dest_row][dest_col];
                    if (board->block[dest_row][dest_col]->owner == PLAYER_1) {
                        cstk = board->dead_player1;
                    }
                    else {
                        cstk = board->dead_player2;
                    }
                    printf("%s的%s已经被击败了", c2tUser(board, dead->owner), chessName(dead));
                    ChessStackPush(cstk, dead);
                    getchar();
                    getchar();
                }
                board->block[dest_row][dest_col] = board->block[src_row][src_col];
                board->block[src_row][src_col] = NULL;
                return true;
            }
        }
    }
    // }
    system("cls");
    printf("不可移动到这里");
    getchar();
    getchar();
    return false;
}

/**
 * @brief 判断游戏是否结束（是否将死）
 * 
 * @param board 棋盘
 * @return int 返回true，如果已经将死；否则返回false
 */
int isGameEnd(struct ChessBoard* board) {
    if (
    (isChessStackEmpty(board->dead_player1) == false && ChessStackTop(board->dead_player1)->type == GENERAL) || 
    (isChessStackEmpty(board->dead_player2) == false && ChessStackTop(board->dead_player2)->type == GENERAL))
        return true;
    else return false;
}
