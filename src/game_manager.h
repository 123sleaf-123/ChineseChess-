#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "chess_board.h"
#include "command.h"


typedef struct {
    struct ChessBoard *board; // 棋盘指针
    Command *command_history; // 操作记录链表头指针
} GameManager;

GameManager *createGameManager(); // 创建游戏管理器

struct ChessBoard *getGameManagerChessBoard(GameManager *manager); // 获取棋盘指针
void setGameManagerChessBoard(GameManager *manager, struct ChessBoard *board); // 设置棋盘指针
Command *getGameManagerCommandHistory(GameManager *manager);                   // 获取操作记录链表头指针
void setGameManagerCommandHistory(GameManager *manager, Command *command_history); // 设置操作记录链表头指针

void addCommandToHistory(GameManager *manager, Command *command);
void removeLastCommandFromHistory(GameManager *manager); 
void clearCommandHistory(GameManager *manager); // 清空操作记录链表

#endif // GAME_MANAGER_H