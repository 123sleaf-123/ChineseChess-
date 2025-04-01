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

char** initMatrix() {
    char **matrix = (char **)malloc(sizeof(char *) * BOARD_ROW);
    for (int i = 0; i < BOARD_ROW; i++)
    {
        matrix[i] = (char *) malloc(sizeof(char) * BOARD_COL);
        for (int j = 0; j < BOARD_COL; j++)
        {
            matrix[i][j] = false;
        } 
    }
    return matrix;
}

void freeMatrix(char **matrix) {
    for (int i = BOARD_ROW-1; i >= 0; --i)
    {
        free(matrix[i]);
    }
    free(matrix);
}

struct ChessBoard* initChessBoard() {
    struct ChessBoard *board = (struct ChessBoard *)malloc(sizeof(struct ChessBoard));
    board->block = (struct Chess ***)malloc(sizeof(struct Chess **) * BOARD_ROW);
    for (int i = 0; i < 10; i++)
    {
        board->block[i] = (struct Chess **)malloc(sizeof(struct Chess *) * BOARD_COL);
        for (int j = 0; j < 9; j++)
        {
            board->block[i][j] = NULL;
        } 
    }
    board->boardBlock = (struct BoardBlock ***)malloc(sizeof(struct BoardBlock **) * BOARD_ROW);
    for (int i = 0; i < 10; i++)
    {
        board->boardBlock[i] = (struct BoardBlock **)malloc(sizeof(struct BoardBlock *) * BOARD_COL);
        for (int j = 0; j < 9; j++)
        {
            board->boardBlock[i][j] = initDefaultBoardBlock();
        }
    }

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
    board->moveablePos = initMatrix();
    board->attackablePos = initMatrix();

    board->user = PLAYER_1; // 开局玩家初始化
    board->chessChoose = NULL;
    board->dead_chess = (struct ChessStack **)malloc(sizeof(struct ChessStack *) * 2);
    board->dead_chess[PLAYER_1] = initChessStack_default();
    board->dead_chess[PLAYER_2] = initChessStack_default();
    board->tip = (struct Tips *)malloc(sizeof(struct Tips));
    board->tip->top = -1;
    board->record = initRecordStack(32);
    return board;
}

bool setChessBoardBlock(struct ChessBoard *board, int row, int col, struct Chess *chess) {
    if ((0 <= row && row < BOARD_ROW) && (0 <= col && col < BOARD_COL)) {
        board->block[row][col] = chess;
        board->boardBlock[row][col]->chess = chess;
        if (chess != NULL) {
            chess->pos->x = row;
            chess->pos->y = col;
        }
        return true;
    }
    else return false;
}

void reset_moveablePos(struct ChessBoard *board) {
    for (int i = 0; i < BOARD_ROW; i++)
    {
        for (int j = 0; j < BOARD_COL; j++)
        {
            board->moveablePos[i][j] = false;
        } 
    }
}

int setChessBoardMoveablePos(struct ChessBoard *board, int row, int col, int val) {
    if ((0 <= row && row < BOARD_ROW) && (0 <= col && col < BOARD_COL)) {
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

struct Chess *getChessByPos(struct ChessBoard *board, int row, int col) {
    if ((0 <= row && row < BOARD_ROW) && (0 <= col && col < BOARD_COL)) {
        return board->block[row][col];
    }
    else return NULL;
}

RecordStack *getRecordStack(struct ChessBoard *board) { return board->record; }

struct Chess *getChessChoose(struct ChessBoard *board) {
  return board->chessChoose;
}

void setChessChoose(struct ChessBoard *board, struct Chess *chess) {
    board->chessChoose = chess;
}

int getBlockMovementCost(struct ChessBoard *board, int row, int col) {
    if (board->boardBlock[row][col] != NULL) {
        return getTerrainCostByBlock(board->boardBlock[row][col]);
    }
    return 0;
}