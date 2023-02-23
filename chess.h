#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#define true 1
#define false 0
#define BOARD_ROW 10
#define BOARD_COL 9
#define GREEN_TEXT 2
#define RED_TEXT 4
#define WHITE_TEXT 7

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

struct chessStack
{
    struct Chess *stack[16];
    int top;
};

typedef struct ChessBoard
{
    struct Chess *block[10][9];
    char moveablePos[10][9];
    int user;
    struct chessStack *dead_player1;
    struct chessStack *dead_player2;
} *Board;

struct Position
{
    int x; // 横坐标
    int y; // 纵坐标
};

Chess initChess(int type, int owner, int isAlive);
struct chessStack* initChessStack();
struct ChessBoard* initChessBoard();
int setChessBoardMovablePos(struct ChessBoard *board, int row, int col, int val);
struct Position* initPosition(int x, int y);
void color(int x);
char *c2tUser(struct ChessBoard* board, int code);
char *chessName(struct Chess* chess);
void actionFinished(struct ChessBoard *board);
int isInside(int row, int col); 
int isNull(struct ChessBoard* board, int row, int col);
int isControllable(struct ChessBoard* board, int row, int col);
int friendlyFireDetect(struct ChessBoard* board, int row, int col);
int isBeyond(struct ChessBoard* board, int row, int col);
int choose(struct ChessBoard* board, int src_row, int src_col);
void moveablePosition(struct ChessBoard* board, int src_row, int src_col);
int isMoveable(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col);
int action(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col);
void printChessBoard(struct ChessBoard* board);
