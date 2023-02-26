#include "global.h"
#include "chess_io.h"
#include "operations.h"

extern void actionFinished(struct ChessBoard *board);
extern bool isGameEnd(struct ChessBoard* board);

int main(int argc, char const *argv[])
{
    // 初始化棋盘
    Board board;
    board = initChessBoard();
    while (true)
    {
        printChessBoard(board);
        char src[10], dest[10];

        Sleep(2000);
        scanf("%s", src);
        Sleep(2000);
        int
            src_row = src[0] - '0',
            src_col = src[1] - '0';

        if (choose(board, src_row, src_col) == false)
            continue; // 一旦执行了该函数，必须在下一循环前使用actionFinished函数

        int dest_row, dest_col, action_res;
        do
        {
            action_res = false;
            printChessBoard(board);
            Sleep(2000);
            scanf("%s", dest);
            Sleep(2000);
            if (strcmp(dest, "cancel") == 0)
            {
                actionFinished(board);
                break;
            }
            dest_row = dest[0] - '0';
            dest_col = dest[1] - '0';
            action_res = move(board, src_row, src_col, dest_row, dest_col);
        } while (action_res == false);
        actionFinished(board);
        if (action_res == true)
        {
            // 如果玩家已经行动
            if (isGameEnd(board) == true)
            {
                printChessBoard(board);
                putchar('\n');
                printf("游戏结束");
                break;
            }
            else
                board->user = !board->user;
        }
    }
    getchar();
    return 0;
}