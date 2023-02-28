#include "global.h"
#include "chess_board.h"

int half_board[5][9] = 
{
    {CHARIOT, HORSE, ELEPHANT, WARRIOR, GENERAL, WARRIOR, ELEPHANT, HORSE, CHARIOT},    // 0
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,},                   // 1
    {EMPTY, ARTILLERY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, ARTILLERY, EMPTY},     // 2
    {SOLDIER, EMPTY, SOLDIER, EMPTY, SOLDIER, EMPTY, SOLDIER, EMPTY, SOLDIER},          // 3
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,},                   // 4
};

struct ChessBoard* initChessBoard() {
    struct ChessBoard *board = (struct ChessBoard *)malloc(sizeof(struct ChessBoard));
    board->objects = initChessStack(32);

    // 玩家一初始化
    for (int i = 4; i >= 0; --i)
    {
        for (int j = 0; j < BOARD_COL; j++)
        {
            placeChess(board, BOARD_ROW - i - 1, j, initChess(half_board[i][j], PLAYER_1, true));
        }
    }

    // 玩家二初始化
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < BOARD_COL; j++)
        {
            placeChess(board, i, j, initChess(half_board[i][j], PLAYER_2, true));
        }
    }
    
    // 可移动区域初始化
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board->moveablePos[i][j] = false;
        } 
    }
    
    board->user = PLAYER_1; // 开局玩家初始化
    board->chessChoose = NULL;
    board->dead_player1 = initChessStack_default();
    board->dead_player2 = initChessStack_default();
    board->tip = (struct Tips *)malloc(sizeof(struct Tips));
    board->tip->top = -1;
    return board;
}

bool setChessBoardBlock(struct ChessBoard *board, int row, int col, struct Chess *chess) {
    if ((0 <= row && row <= 9) && (0 <= col && col <= 8)) {
        board->block[row][col] = chess;
        if (chess != NULL) {
            chess->pos.x = row;
            chess->pos.y = col;
        }
        return true;
    }
    else return false;
}

int setChessBoardMoveablePos(struct ChessBoard *board, int row, int col, int val) {
    if ((0 <= row && row <= 9) && (0 <= col && col <= 8)) {
        board->moveablePos[row][col] = val;
        return true;
    }
    else return false;
}

bool placeChess(struct ChessBoard *board, int row, int col, struct Chess *chess) {
    if (chess != NULL) {
        ChessStackPush(board->objects, chess);
    }
    return setChessBoardBlock(board, row, col, chess);
}