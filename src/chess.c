#include "chess.h"
#include "property_fight.h"

int count = 0;

struct Chess *initChess(int type, int owner, int is_alive) {
    if (type == EMPTY)
        return NULL;
    struct Chess* chess = (struct Chess*) malloc(sizeof(struct Chess));
    chess->id = count++;
    chess->type = type;
    chess->owner = owner;
    chess->is_alive = is_alive;
    chess->battle_property = initDefaultBattleProperty();
    chess->pos = initPosition(0, 0);
    return chess;
}

struct Position *initPosition(int x, int y) {
    struct Position* pos = (struct Position*) malloc(sizeof(struct Position));
    pos->x = x;
    pos->y = y;
    return pos;
}

struct Position *getChessPosition(struct Chess *chess) {
    return chess->pos;
}

int getChessMovement(struct Chess *chess) {
    return chess->battle_property->movement;
}

int getChessMinRange(struct Chess *chess) {
    return getAttackMinRange(getBattleProperty(chess));
}

void setChessMinRange(struct Chess *chess, int min_range) {
    setAttackMinRange(getBattleProperty(chess), min_range);
}

int getChessMaxRange(struct Chess *chess) {
    return getAttackMaxRange(getBattleProperty(chess));
}

void setChessMaxRange(struct Chess *chess, int max_range) {
    setAttackMaxRange(getBattleProperty(chess), max_range);
}

bool isInsideAttackRangeByChess(struct Chess *attacker, struct Chess *defender) {
    struct Position *atttacker_pos = getChessPosition(attacker);
    struct Position *defender_pos = getChessPosition(defender);
    int min_range = getAttackMinRange(attacker->battle_property);
    int max_range = getAttackMaxRange(attacker->battle_property);
    return isInsideAttackRangeByPos(atttacker_pos->x, atttacker_pos->y, defender_pos->x, defender_pos->y, min_range, max_range);
}

bool isInsideAttackRangeByPos(int attacker_row, int attacker_col, int defender_row, int defender_col, int min_range, int max_range) {
    int distance = abs(attacker_row - defender_row) + abs(attacker_col - defender_col);
    return (distance >= min_range && distance <= max_range);
}

void printChessBattleProperty(struct Chess *chess) {
    if (chess == NULL || chess->battle_property == NULL) return;
    BattleProperty *bp = chess->battle_property;
    printBattleProperty(bp);
}

BattleProperty *getBattleProperty(struct Chess *chess) {
    return chess->battle_property;
}

