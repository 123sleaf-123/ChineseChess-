#ifndef CHESS_H
#define CHESS_H

typedef int PLAYER;
typedef struct Chess
{
    int id;
    int type;
    PLAYER owner; // 
    char is_alive;
} *ChessPtr;

struct Position
{
    int x; // 横坐标
    int y; // 纵坐标
};

struct Chess *initChess(int type, int owner, int is_alive);
struct Position* initPosition(int x, int y);

#endif