#include "global.h"
#include "chess_io.h"
#include "tools.h"

int color_printf(int text_color, const char *format, ...) {
    color(text_color);
    va_list args;           // 定义一个va_list类型的变量，用来储存单个参数
    va_start(args, format); // 使args指向可变参数的第一个参数
    int len = vprintf(format, args);  // 必须用带v的
    va_end(args);           // 结束可变参数的获取
    color(WHITE_TEXT);
    return len;
}

int autoColor_printf(int user, const char *format, ...) {
    int text_color = WHITE_TEXT;
    if (user == PLAYER_1) text_color = RED_TEXT;
    if (user == PLAYER_2) text_color = GREEN_TEXT;
    color(text_color);
    va_list args;           // 定义一个va_list类型的变量，用来储存单个参数
    va_start(args, format); // 使args指向可变参数的第一个参数
    int len = vprintf(format, args);  // 必须用带v的
    va_end(args);           // 结束可变参数的获取
    color(WHITE_TEXT);
    return len;
}

void printChessBoard(struct ChessBoard* board) {
    system("cls"); // 更新界面，windows为"cls"，linux为""
    printf("  ");
    for (int i = 0; i < 9; i++)
    {
        printf("%d  ", i);
    }
    putchar('\n');  
    // putchar('\n');
    
    for (int i = 0; i < BOARD_ROW; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < BOARD_COL; j++)
        {
            if(board->block[i][j] == NULL) {
                if (board->moveablePos != NULL && board->moveablePos[i][j] == true) {
                    printf("++");
                }
                else {
                    printf("**");
                }
            }
            else {
                if (board->block[i][j] == board->chessChoose) color_printf(BLUE_TEXT, "%s", chessName(board->block[i][j]));
                else autoColor_printf(board->block[i][j]->owner, "%s", chessName(board->block[i][j]));
            }
            putchar(' ');
        }
        // color(WHITE_TEXT);
        putchar('\n');
    }

    // 打印玩家击败的棋子
    printf("玩家一\t");
    for (int i = 0; i <= board->dead_player2->top; i++)
    {
        autoColor_printf(PLAYER_2, "%s ", chessName(board->dead_player2->stack[i]));
    }

    putchar('\n');
    printf("玩家二\t");
    for (int i = 0; i <= board->dead_player1->top; i++)
    {
        autoColor_printf(PLAYER_1, "%s ", chessName(board->dead_player1->stack[i]));
    }
    putchar('\n');

    // 提示当前操作玩家及其颜色
    printf("当前操作玩家：");
    autoColor_printf(board->user, "%s\n", c2tUser(board, board->user));

    printf("当前选中棋子：");
    if (board->chessChoose == NULL) printf("未选中棋子\n");
    else autoColor_printf(board->chessChoose->owner, "%s\n", chessName(board->chessChoose));
}