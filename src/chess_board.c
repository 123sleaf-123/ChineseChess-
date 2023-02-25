#include "global.h"
#include "chess_board.h"

struct ChessBoard* initChessBoard() {
    struct ChessBoard* board = (struct ChessBoard*) malloc(sizeof(struct ChessBoard));
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board->block[i][j] = NULL;
        }
    }
    board->objects = initChessStack_default();

    // 玩家一初始化
    board->block[9][4] = initChess(GENERAL, PLAYER_1, true);

    board->block[9][3] = initChess(WARRIOR, PLAYER_1, true);
    board->block[9][5] = initChess(WARRIOR, PLAYER_1, true);

    
    board->block[9][2] = initChess(ELEPHANT, PLAYER_1, true);
    board->block[9][6] = initChess(ELEPHANT, PLAYER_1, true);

    
    board->block[9][1] = initChess(HORSE, PLAYER_1, true);
    board->block[9][7] = initChess(HORSE, PLAYER_1, true);

    
    board->block[9][0] = initChess(CHARIOT, PLAYER_1, true);
    board->block[9][8] = initChess(CHARIOT, PLAYER_1, true);

    
    board->block[7][1] = initChess(ARTILLERY, PLAYER_1, true);
    board->block[7][7] = initChess(ARTILLERY, PLAYER_1, true);

    board->block[6][0] = initChess(SOLDIER, PLAYER_1, true);
    board->block[6][2] = initChess(SOLDIER, PLAYER_1, true);
    board->block[6][4] = initChess(SOLDIER, PLAYER_1, true);
    board->block[6][6] = initChess(SOLDIER, PLAYER_1, true);
    board->block[6][8] = initChess(SOLDIER, PLAYER_1, true);

    // 玩家二初始化
    board->block[0][4] = initChess(GENERAL, PLAYER_2, true);

    board->block[0][3] = initChess(WARRIOR, PLAYER_2, true);
    board->block[0][5] = initChess(WARRIOR, PLAYER_2, true);

    
    board->block[0][2] = initChess(ELEPHANT, PLAYER_2, true);
    board->block[0][6] = initChess(ELEPHANT, PLAYER_2, true);

    
    board->block[0][1] = initChess(HORSE, PLAYER_2, true);
    board->block[0][7] = initChess(HORSE, PLAYER_2, true);

    
    board->block[0][0] = initChess(CHARIOT, PLAYER_2, true);
    board->block[0][8] = initChess(CHARIOT, PLAYER_2, true);

    
    board->block[2][1] = initChess(ARTILLERY, PLAYER_2, true);
    board->block[2][7] = initChess(ARTILLERY, PLAYER_2, true);

    board->block[3][0] = initChess(SOLDIER, PLAYER_2, true);
    board->block[3][2] = initChess(SOLDIER, PLAYER_2, true);
    board->block[3][4] = initChess(SOLDIER, PLAYER_2, true);
    board->block[3][6] = initChess(SOLDIER, PLAYER_2, true);
    board->block[3][8] = initChess(SOLDIER, PLAYER_2, true);
    
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
    return board;
}

int setChessBoardMoveablePos(struct ChessBoard *board, int row, int col, int val) {
    if ((0 <= row && row <= 9) && (0 <= col && col <= 8)) {
        board->moveablePos[row][col] = val;
        return true;
    }
    else return false;
}