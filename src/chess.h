#ifndef CHESS_H
#define CHESS_H

#include "global.h"
#include "property_fight.h"

typedef int PLAYER;

typedef struct Chess
{
    int id;
    int type;
    PLAYER owner; // 
    char is_alive;
    struct Position *pos;
    BattleProperty *battle_property;
} *ChessPtr;

struct Chess *initChess(int type, int owner, int is_alive);
struct Position *initPosition(int x, int y);
struct Position *getChessPosition(struct Chess *chess);
int getChessMovement(struct Chess *chess);
bool isInsideAttackRangeByChess(struct Chess *attacker, struct Chess *defender);
bool isInsideAttackRangeByPos(int attacker_row, int attacker_col, int defender_row, int defender_col, int range);

#endif