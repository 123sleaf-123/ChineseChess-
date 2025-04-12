#ifndef COMMAND_H
#define COMMAND_H

// 游戏操作类型（枚举）
#include "chess_board.h"
typedef enum {
    MOVE,
    ATTACK,
    HEAL,
    SUMMON,
    APPLY_BUFF
} ActionType;

// 操作记录（基类）
typedef struct Command {
    ActionType type;
    void (*execute)(struct Command*);  // 执行函数指针
    void (*undo)(struct Command*);     // 撤销函数指针
    struct Command *next;              // 链表指针
    struct ChessBoard *board; // 棋盘指针
} Command;

#endif // COMMAND_H