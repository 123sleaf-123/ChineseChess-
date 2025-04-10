#include "chess.h"
#include "character.h"
#include "property_fight.h"

int count = 0;

struct Chess *initChess(int type, int owner, int is_alive) {
    if (type == EMPTY)
        return NULL;
    struct Chess *chess = (struct Chess *)malloc(sizeof(struct Chess));
    chess->id = count++;
    chess->type = type;
    chess->owner = owner;
    chess->is_alive = is_alive;
    chess->pos = initPosition(0, 0);
    chess->character = createCharacterDeault();
    return chess;
}

struct Position *initPosition(int x, int y) {
    struct Position *pos = (struct Position *)malloc(sizeof(struct Position));
    pos->x = x;
    pos->y = y;
    return pos;
}

struct Position *getChessPosition(struct Chess *chess) {
    return chess->pos;
}

Character *getChessCharacter(struct Chess *chess) {
    return chess->character;
}

int getChessMovement(struct Chess *chess) {
    return getMovement(getCharacterBattleProperty(chess->character));
}

int getChessMinRange(struct Chess *chess) {
    return getAttackMinRange(getCharacterBattleProperty(chess->character));
}

void setChessMinRange(struct Chess *chess, int min_range) {
    setAttackMinRange(getCharacterBattleProperty(chess->character), min_range);
}

int getChessMaxRange(struct Chess *chess) {
    return getAttackMaxRange(getCharacterBattleProperty(chess->character));
}

void setChessMaxRange(struct Chess *chess, int max_range) {
    setAttackMaxRange(getCharacterBattleProperty(chess->character), max_range);
}

BattleProperty *getChessBattleProperty(struct Chess *chess) {
    return getCharacterBattleProperty(chess->character);
}

Knapsack *getChessKnapsack(struct Chess *chess) {
    if (chess == NULL)
        return NULL;
    return chess->character->knapsack;
}

bool isInsideAttackRangeByChess(struct Chess *attacker, struct Chess *defender) {
    struct Position *atttacker_pos = getChessPosition(attacker);
    struct Position *defender_pos = getChessPosition(defender);
    int min_range = getAttackMinRange(getChessBattleProperty(attacker));
    int max_range = getAttackMaxRange(getChessBattleProperty(attacker));
    return isInsideAttackRangeByPos(atttacker_pos->x, atttacker_pos->y, defender_pos->x, defender_pos->y, min_range,
                                    max_range);
}

bool isInsideAttackRangeByPos(int attacker_row, int attacker_col, int defender_row, int defender_col, int min_range,
                              int max_range) {
    int distance = abs(attacker_row - defender_row) + abs(attacker_col - defender_col);
    return (distance >= min_range && distance <= max_range);
}

void printChessBattleProperty(struct Chess *chess) {
    if (chess == NULL || getChessBattleProperty(chess) == NULL)
        return;
    BattleProperty *bp = getChessBattleProperty(chess);
    printBattleProperty(bp);
}

void recoverChess(struct Chess *chess, int health) {
    if (chess == NULL)
        return;
    chess->is_alive = true;
    BattleProperty *bp = getChessBattleProperty(chess);
    setHealth(bp, getHealth(bp) + health);
}

void takeDamageChess(struct Chess *chess, int damage) {
    if (chess == NULL)
        return;
    BattleProperty *bp = getChessBattleProperty(chess);
    setHealth(bp, getHealth(bp) - damage);
}
