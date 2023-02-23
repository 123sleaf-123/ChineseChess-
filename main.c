#include "chess.c"
#include <string.h>

int main(int argc, char const *argv[])
{   
    // 初始化棋盘
    Board board;
    board = initChessBoard();
    while(true) {
        printChessBoard(board);
        char src[10], dest[10];

        scanf("%s", src);
        int 
        src_row = src[0] - '0', 
        src_col = src[1] - '0';

        if (choose(board, src_row, src_col) == false) 
            continue; // 一旦执行了该函数，必须在下一循环前使用actionFinished函数

        int dest_row, dest_col, action_res;
        do {
            printChessBoard(board);
            scanf("%s", dest);
            if (strcmp(dest, "cancel") == 0) {
                actionFinished(board);
                break;
            }
            dest_row = dest[0] - '0';
            dest_col = dest[1] - '0';
            action_res = action(board, src_row, src_col, dest_row, dest_col);
        } while (action_res == false);
        if (action_res == true) board->user = !board->user;
        actionFinished(board);
    }
    getchar();
    return 0;
}