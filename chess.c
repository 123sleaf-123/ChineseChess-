#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define true 1
#define false 0
#define BOARD_ROW 10
#define BOARD_COL 9

typedef struct Chess
{
    int type;
    int owner; // 
    int isAlive;
} *Chess;

// block type
#define EMPTY 0
#define GENERAL 1 // 将/帅
#define CHARIOT 2 // 车
#define HORSE 3 // 马
#define ARTILLERY 4 // 炮
#define ELEPHANT 5 // 象/相
#define WARRIOR 6 // 士/仕
#define SOLIDER 7 // 卒

// owner
#define PLAYER_1 0
#define PLAYER_2 1
#define SPARE 3

// isAlive
#define DEAD false
#define ALIVE true

Chess initChess(int type, int owner, int isAlive);
Chess initChess(int type, int owner, int isAlive) {
    struct Chess* ch = (Chess) malloc(sizeof(struct Chess));
    ch->type = type;
    ch->owner = owner;
    ch->isAlive = isAlive;
    return ch;
}

struct chessStack
{
    struct Chess *stack[16];
    int top;
};

struct chessStack* initChessStack() {
    struct chessStack* stk = (struct chessStack*) malloc(sizeof(struct chessStack));
    stk->top = 0;
}

typedef struct ChessBoard
{
    struct Chess *block[10][9];
    int user;
    struct chessStack *dead_player1;
    struct chessStack *dead_player2;
} *Board;

struct ChessBoard* init();
struct ChessBoard* init() {
    struct ChessBoard* board = (struct ChessBoard*) malloc(sizeof(struct ChessBoard));
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board->block[i][j] = NULL;
        }
    }

    // 玩家一初始化
    board->block[9][4] = initChess(GENERAL, PLAYER_1, true);

    board->block[9][3] = initChess(WARRIOR, PLAYER_1, true);
    board->block[9][5] = initChess(WARRIOR, PLAYER_1, true);

    
    board->block[9][2] = initChess(ELEPHANT, PLAYER_1, true);
    board->block[9][6] = initChess(ELEPHANT, PLAYER_1, true);

    
    board->block[9][1] = initChess(HORSE, PLAYER_1, true);
    board->block[9][7] = initChess(HORSE, PLAYER_1, true);

    
    board->block[9][0] = initChess(CHARIOT, PLAYER_1, true);
    board->block[9][8] = initChess(CHARIOT, PLAYER_1, true);

    
    board->block[7][1] = initChess(ARTILLERY, PLAYER_1, true);
    board->block[7][7] = initChess(ARTILLERY, PLAYER_1, true);

    board->block[6][0] = initChess(SOLIDER, PLAYER_1, true);
    board->block[6][2] = initChess(SOLIDER, PLAYER_1, true);
    board->block[6][4] = initChess(SOLIDER, PLAYER_1, true);
    board->block[6][6] = initChess(SOLIDER, PLAYER_1, true);
    board->block[6][8] = initChess(SOLIDER, PLAYER_1, true);

    // 玩家二初始化
    board->block[0][4] = initChess(GENERAL, PLAYER_2, true);

    board->block[0][3] = initChess(WARRIOR, PLAYER_2, true);
    board->block[0][5] = initChess(WARRIOR, PLAYER_2, true);

    
    board->block[0][2] = initChess(ELEPHANT, PLAYER_2, true);
    board->block[0][6] = initChess(ELEPHANT, PLAYER_2, true);

    
    board->block[0][1] = initChess(HORSE, PLAYER_2, true);
    board->block[0][7] = initChess(HORSE, PLAYER_2, true);

    
    board->block[0][0] = initChess(CHARIOT, PLAYER_2, true);
    board->block[0][8] = initChess(CHARIOT, PLAYER_2, true);

    
    board->block[2][1] = initChess(ARTILLERY, PLAYER_2, true);
    board->block[2][7] = initChess(ARTILLERY, PLAYER_2, true);

    board->block[3][0] = initChess(SOLIDER, PLAYER_2, true);
    board->block[3][2] = initChess(SOLIDER, PLAYER_2, true);
    board->block[3][4] = initChess(SOLIDER, PLAYER_2, true);
    board->block[3][6] = initChess(SOLIDER, PLAYER_2, true);
    board->block[3][8] = initChess(SOLIDER, PLAYER_2, true);
    
    board->user = PLAYER_1;
    board->dead_player1 = initChessStack();
    board->dead_player2 = initChessStack();
}

/*
    1.不可移动：
        1.1. 原位置不存在己方棋子或不存在棋子
        1.2. 目标位置超出棋盘范围
        1.3. 目标位置存在己方棋子
        1.4. 不符合棋子移动规则
    2. 可移动：操纵了己方棋子，未超出棋盘范围，且符合移动规则，且目标位置不存在己方棋子
*/

// 原位置是否存在棋子，且棋子为己方棋子
int isControllable(struct ChessBoard* board, int row, int col);
int isControllable(struct ChessBoard* board, int row, int col) {
    return board->block[row][col] != NULL && board->block[row][col]->owner == board->user;
}

// 是否超出棋盘范围
int isInside(int row, int col); 
int isInside(int row, int col) {
    return row < BOARD_ROW && col < BOARD_COL;
}

/**
 * @brief 目标位置是否存在己方棋子，是否会造成友伤
 * 
 * @param board 棋盘
 * @param row 目标行
 * @param col 目标列
 * @return int 返回true，若目标位置为我方棋子；返回false，若目标位置为空或敌方棋子
 */
int friendlyFireDetect(struct ChessBoard* board, int row, int col);
int friendlyFireDetect(struct ChessBoard* board, int row, int col) {
    return board->block[row][col]->owner == board->user;
}

// 是否符合棋子移动规则
int isMoveable(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col);
int isMoveable(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col) {
    struct Chess* chess = board->block[src_row][src_col];
    int distance_square 
    = (dest_row - src_row) * (dest_row - src_row) 
    + (dest_col - src_col) * (dest_col - src_col);
    if (distance_square == 0) return false;

    switch (chess->type) {
        case GENERAL: // 是否在九宫格内且移动了一格
        {
            int inside = (dest_row >= 0) && (dest_row < 3) && (dest_col > 2) && (dest_col < 6);
            return inside && distance_square <= 2;
        }
        case CHARIOT: // 目标位置与源位置是否在同一行或同一列
            return dest_row == src_row || dest_col == src_col;
        case HORSE: // 是否移动了三格
            return distance_square <= 5;
        case ARTILLERY: 
            // 目标位置与源位置是否在同一行或同一列
            // 且目标位置有敌人，目标位置与源位置之间是否有棋子
            if (dest_row == src_row || dest_col == src_col) {
                if (board->block[dest_row][dest_col]->owner != board->user) {
                    if (dest_row == src_row) {
                        int begin = (src_col < dest_col ? src_col : dest_col) + 1;
                        int end = src_col < dest_col ? dest_col : src_col;
                        for (int i = begin; i < end; i++)
                        {
                            if (board->block[dest_row][i] != NULL) return true;
                        }
                        return false;
                    }
                    if (dest_col == src_col) {
                        int begin = (src_row < dest_row ? src_row : dest_row) + 1;
                        int end = src_row < dest_row ? dest_row : src_row;
                        for (int i = begin; i < end; i++)
                        {
                            if (board->block[i][dest_col] != NULL) return true;
                        }
                        return false;
                    }
                    return true;
                }
            }
            else return false;
        // case
        // case
        // case
    }
    // if (chess->type == GENERAL) {
    //     inside = dest_row >= 0 && dest_row < 3 && dest_col > 2 && dest_col < 6;
    // }
}

void action(struct ChessBoard* board);
void action(struct ChessBoard* board) {
    char src[3], dest[3];
    scanf("%s %s", src, dest);
    int 
    src_row = src[0] - '0', 
    src_col = src[1] - '0', 
    dest_row = dest[0] - '0', 
    dest_col = dest[1] - '0';

    if (src_row < BOARD_ROW && src_col < BOARD_COL 
    && board->block[src_row][src_col] != NULL 
    && dest_row < BOARD_ROW && src_col < BOARD_COL) {
        if (board->block[dest_row][dest_col] != NULL) {
            if (board->block[dest_row][dest_col]->owner == board->block[src_row][src_col]->owner) {
                system("cls");
                printf("不可移动到这里");
                getchar();
                getchar();
                return;
            }
            else {
                struct chessStack *cstk;
                struct Chess *dead = board->block[dest_row][dest_col];
                if (board->block[dest_row][dest_col]->owner == PLAYER_1) {
                    cstk = board->dead_player1;
                    printf("玩家一的%d已经被击败了", dead->type);
                }
                else {
                    cstk = board->dead_player2;
                    printf("玩家二的%d已经被击败了", dead->type);
                }
                cstk->stack[cstk->top++] = dead;
                getchar();
                getchar();
            }
        }
        board->block[dest_row][dest_col] = board->block[src_row][src_col];
        board->block[src_row][src_col] = NULL;
    }
    // while (getchar() != '\n'); // 消除不必要的字符
}

void printChessBoard(struct ChessBoard* board);
void printChessBoard(struct ChessBoard* board) {
    printf("  ");
    for (int i = 0; i < 9; i++)
    {
        printf("%d", i);
    }
    putchar('\n');  putchar('\n');
    
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < 9; j++)
        {
            if(board->block[i][j] == NULL) printf("*");
            else {
                // if (board->block[i][j]->type == GENERAL 
                // && board->block[i][j]->owner == PLAYER_1 
                // && board->block[i][j]->isAlive == true) printf("帥");
                // else 
                printf("%d", board->block[i][j]->type);
            }
        }
        putchar('\n');
    }

    // 打印死亡棋子
    printf("玩家一\t");
    for (int i = 0; i < board->dead_player2->top; i++)
    {
        printf("%d ", board->dead_player2->stack[i]->type);
    }

    putchar('\n');
    printf("玩家二\t");
    for (int i = 0; i < board->dead_player1->top; i++)
    {
        printf("%d ", board->dead_player1->stack[i]->type);
    }
    putchar('\n');
}

int main(int argc, char const *argv[])
{   
    // 初始化棋盘
    Board board;
    board = init();
    while(true) {
        printChessBoard(board);
        action(board);
        board->user = !board->user;
        system("cls"); // 更新界面，windows为"cls"，linux为""
    // printChessBoard(board);
    }
    // while(true) ;
    getchar();
    return 0;
}
