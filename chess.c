#include "chess.h"
#include <stdarg.h>

struct ChessStack* initChessStack(int maxSize) {
    struct ChessStack* stack = (struct ChessStack*) malloc(sizeof(struct ChessStack));
    stack->stack = (struct Chess**) malloc(sizeof(struct Chess*) * maxSize);
    stack->top = -1;
    stack->maxSize = maxSize;
    return stack;
}

struct ChessStack* initChessStack_default() {
    return initChessStack(16);
}

/**
 * @brief 判断栈是否为空
 * 
 * @param stack 棋子的栈
 * @return int 返回true，如果栈为空；返回false，若果栈非空
 */
int isChessStackEmpty(struct ChessStack *chess_stk) {
    if (chess_stk->top == -1) return true;
    else return false;
}

int ChessStackPush(struct ChessStack *chess_stk, struct Chess *chess) {
    if (chess_stk->top < chess_stk->maxSize) {
        chess_stk->stack[++chess_stk->top] = chess;
        return true;
    }
    else return false;
}

struct Chess *ChessStackTop(struct ChessStack *chess_stk) {
    if (isChessStackEmpty(chess_stk) == true) return NULL;
    else return chess_stk->stack[chess_stk->top];
}

Chess initChess(struct ChessBoard *board, int type, int owner, int isAlive) {
    struct Chess* chess = (Chess) malloc(sizeof(struct Chess));
    chess->id = board->objects->top;
    chess->type = type;
    chess->owner = owner;
    chess->isAlive = isAlive;
    ChessStackPush(board->objects, chess);
    return chess;
}

struct ChessBoard* initChessBoard() {
    struct ChessBoard* board = (struct ChessBoard*) malloc(sizeof(struct ChessBoard));
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board->block[i][j] = NULL;
        }
    }
    board->objects = initChessStack_default();

    // 玩家一初始化
    board->block[9][4] = initChess(board, GENERAL, PLAYER_1, true);

    board->block[9][3] = initChess(board, WARRIOR, PLAYER_1, true);
    board->block[9][5] = initChess(board, WARRIOR, PLAYER_1, true);

    
    board->block[9][2] = initChess(board, ELEPHANT, PLAYER_1, true);
    board->block[9][6] = initChess(board, ELEPHANT, PLAYER_1, true);

    
    board->block[9][1] = initChess(board, HORSE, PLAYER_1, true);
    board->block[9][7] = initChess(board, HORSE, PLAYER_1, true);

    
    board->block[9][0] = initChess(board, CHARIOT, PLAYER_1, true);
    board->block[9][8] = initChess(board, CHARIOT, PLAYER_1, true);

    
    board->block[7][1] = initChess(board, ARTILLERY, PLAYER_1, true);
    board->block[7][7] = initChess(board, ARTILLERY, PLAYER_1, true);

    board->block[6][0] = initChess(board, SOLDIER, PLAYER_1, true);
    board->block[6][2] = initChess(board, SOLDIER, PLAYER_1, true);
    board->block[6][4] = initChess(board, SOLDIER, PLAYER_1, true);
    board->block[6][6] = initChess(board, SOLDIER, PLAYER_1, true);
    board->block[6][8] = initChess(board, SOLDIER, PLAYER_1, true);

    // 玩家二初始化
    board->block[0][4] = initChess(board, GENERAL, PLAYER_2, true);

    board->block[0][3] = initChess(board, WARRIOR, PLAYER_2, true);
    board->block[0][5] = initChess(board, WARRIOR, PLAYER_2, true);

    
    board->block[0][2] = initChess(board, ELEPHANT, PLAYER_2, true);
    board->block[0][6] = initChess(board, ELEPHANT, PLAYER_2, true);

    
    board->block[0][1] = initChess(board, HORSE, PLAYER_2, true);
    board->block[0][7] = initChess(board, HORSE, PLAYER_2, true);

    
    board->block[0][0] = initChess(board, CHARIOT, PLAYER_2, true);
    board->block[0][8] = initChess(board, CHARIOT, PLAYER_2, true);

    
    board->block[2][1] = initChess(board, ARTILLERY, PLAYER_2, true);
    board->block[2][7] = initChess(board, ARTILLERY, PLAYER_2, true);

    board->block[3][0] = initChess(board, SOLDIER, PLAYER_2, true);
    board->block[3][2] = initChess(board, SOLDIER, PLAYER_2, true);
    board->block[3][4] = initChess(board, SOLDIER, PLAYER_2, true);
    board->block[3][6] = initChess(board, SOLDIER, PLAYER_2, true);
    board->block[3][8] = initChess(board, SOLDIER, PLAYER_2, true);
    
    // 可移动区域初始化
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board->moveablePos[i][j] = false;
        } 
    }
    
    board->user = PLAYER_1; // 开局玩家初始化
    board->chessChoose = NULL;
    board->dead_player1 = initChessStack_default();
    board->dead_player2 = initChessStack_default();
}

int setChessBoardMoveablePos(struct ChessBoard *board, int row, int col, int val) {
    if ((0 <= row && row <= 9) && (0 <= col && col <= 8)) {
        board->moveablePos[row][col] = val;
        return true;
    }
    else return false;
}

struct Position* initPosition(int x, int y) {
    struct Position* pos = (struct Position*) malloc(sizeof(struct Position));
    pos->x = x;
    pos->y = y;
    return pos;
}

/**
 * @brief 设置文字颜色
 * 
 * @param x 颜色代码
 */
void color(int x) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

char *c2tUser(struct ChessBoard* board, int code) {
    if (code == PLAYER_1) return "玩家一";
    if (code == PLAYER_2) return "玩家二";
    return "";
}

/**
 * @brief 输入棋子，输出棋子中文名字，区分玩家
 * 
 * @param chess 玩家棋子
 * @return char* 棋子中文名字
 */
char *chessName(struct Chess* chess) {
    switch(chess->owner) {
        // 玩家一是红色
        case PLAYER_1: {
            switch(chess->type) {
                case GENERAL: return "帥";
                case CHARIOT: return "俥";
                case HORSE: return "傌";
                case ARTILLERY: return "炮";
                case ELEPHANT: return "相";
                case WARRIOR: return "仕";
                case SOLDIER: return "兵";
            }
            break;
        }

        // 玩家二是绿色
        case PLAYER_2: {
            switch(chess->type) {
                case GENERAL: return "将";
                case CHARIOT: return "車";
                case HORSE: return "馬";
                case ARTILLERY: return "砲";
                case ELEPHANT: return "象";
                case WARRIOR: return "士";
                case SOLDIER: return "卒";
            }
            break;
        }
    }

    return " ";
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
}

int isInsidePalace(struct ChessBoard* board, int row, int col) {
    if (board->user == PLAYER_1) 
        return (7 <= row) && (row <= 9) && (3 <= col) && (col <= 5);
    if (board->user == PLAYER_2) 
        return (0 <= row) && (row <= 2) && (3 <= col) && (col <= 5);
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
            int dest_row[4], dest_col[4], inside;
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

int color_printf(int text_color, const char *format, ...) {
    color(text_color);
    va_list args;           // 定义一个va_list类型的变量，用来储存单个参数
    va_start(args, format); // 使args指向可变参数的第一个参数
    int len = vprintf(format, args);  // 必须用带v的
    va_end(args);           // 结束可变参数的获取
    color(WHITE_TEXT);
    return len;
}

int autoColor_printf(int user, const char *format, ...) {
    int text_color = WHITE_TEXT;
    if (user == PLAYER_1) text_color = RED_TEXT;
    if (user == PLAYER_2) text_color = GREEN_TEXT;
    color(text_color);
    va_list args;           // 定义一个va_list类型的变量，用来储存单个参数
    va_start(args, format); // 使args指向可变参数的第一个参数
    int len = vprintf(format, args);  // 必须用带v的
    va_end(args);           // 结束可变参数的获取
    color(WHITE_TEXT);
    return len;
}

void printChessBoard(struct ChessBoard* board) {
    system("cls"); // 更新界面，windows为"cls"，linux为""
    printf("  ");
    for (int i = 0; i < 9; i++)
    {
        printf("%d  ", i);
    }
    putchar('\n');  
    // putchar('\n');
    
    for (int i = 0; i < BOARD_ROW; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < BOARD_COL; j++)
        {
            if(board->block[i][j] == NULL) {
                if (board->moveablePos != NULL && board->moveablePos[i][j] == true) {
                    printf("++");
                }
                else {
                    printf("**");
                }
            }
            else {
                if (board->block[i][j] == board->chessChoose) color_printf(BLUE_TEXT, "%s", chessName(board->block[i][j]));
                else autoColor_printf(board->block[i][j]->owner, "%s", chessName(board->block[i][j]));
            }
            putchar(' ');
        }
        // color(WHITE_TEXT);
        putchar('\n');
    }

    // 打印玩家击败的棋子
    printf("玩家一\t");
    for (int i = 0; i <= board->dead_player2->top; i++)
    {
        autoColor_printf(PLAYER_2, "%s ", chessName(board->dead_player2->stack[i]));
    }

    putchar('\n');
    printf("玩家二\t");
    for (int i = 0; i <= board->dead_player1->top; i++)
    {
        autoColor_printf(PLAYER_1, "%s ", chessName(board->dead_player1->stack[i]));
    }
    putchar('\n');

    // 提示当前操作玩家及其颜色
    printf("当前操作玩家：");
    autoColor_printf(board->user, "%s\n", c2tUser(board, board->user));

    printf("当前选中棋子：");
    if (board->chessChoose == NULL) printf("未选中棋子\n");
    else autoColor_printf(board->chessChoose->owner, "%s\n", chessName(board->chessChoose));
}
