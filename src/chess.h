#ifndef CHESS_H
#define CHESS_H

#include "global.h"

typedef int PLAYER;

typedef struct Chess
{
    int id;
    int type;
    PLAYER owner; // 
    char is_alive;
    struct Position pos;
} *ChessPtr;

struct Chess *initChess(int type, int owner, int is_alive);
struct Position* initPosition(int x, int y);

#endif