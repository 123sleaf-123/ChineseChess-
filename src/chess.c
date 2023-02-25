#include "global.h"
#include "chess.h"
#include "chess_stack.h"

struct ChessStack objects;

struct Chess *initChess(int type, int owner, int is_alive) {
    struct Chess* chess = (struct Chess*) malloc(sizeof(struct Chess));
    chess->id = objects.top;
    chess->type = type;
    chess->owner = owner;
    chess->is_alive = is_alive;
    ChessStackPush(&objects, chess);
    return chess;
}

struct Position* initPosition(int x, int y) {
    struct Position* pos = (struct Position*) malloc(sizeof(struct Position));
    pos->x = x;
    pos->y = y;
    return pos;
}
