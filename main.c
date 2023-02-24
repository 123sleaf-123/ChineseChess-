#include "chess.c"
#include <string.h>

int main(int argc, char const *argv[])
{   
    // ��ʼ������
    Board board;
    board = initChessBoard();
    while(true) {
        printChessBoard(board);
        char src[10], dest[10];

        Sleep(2000);
        scanf("%s", src);
        Sleep(1000);
        int 
        src_row = src[0] - '0', 
        src_col = src[1] - '0';

        if (choose(board, src_row, src_col) == false) 
            continue; // һ��ִ���˸ú�������������һѭ��ǰʹ��actionFinished����

        int dest_row, dest_col, action_res;
        do {
            action_res = false;
            printChessBoard(board);
            Sleep(2000);
            scanf("%s", dest);
            Sleep(2000);
            if (strcmp(dest, "cancel") == 0) {
                actionFinished(board);
                break;
            }
            dest_row = dest[0] - '0';
            dest_col = dest[1] - '0';
            action_res = action(board, src_row, src_col, dest_row, dest_col);
        } while (action_res == false);
        actionFinished(board);
        if (action_res == true) {
            // �������Ѿ��ж�
            if (isGameEnd(board) == true) {
                printChessBoard(board);
                putchar('\n');
                printf("��Ϸ����");
                break;
            }
            else board->user = !board->user;
        }
    }
    getchar();
    return 0;
}