#include "chess_io.h"
#include "chess_board.h"
#include "tools.h"

char *PlayerInput() {
    char *input = (char *)malloc(sizeof(char) * 10);
    scanf("%9s", input);  // 防止缓冲区溢出
    return input;
}

Cmd init_player_command(int command_type, ...) {
    va_list args;

    Cmd cmd = (Cmd)malloc(sizeof(struct PlayerCommand));
    if (cmd != NULL) {
        cmd->command_type = command_type;
        // 根据实际需求添加参数处理
    }
    return cmd;
}

void clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD written;

    // 获取控制台缓冲区信息
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }

    DWORD cells = csbi.dwSize.X * csbi.dwSize.Y;
    COORD topLeft = {0, 0};

    // 填充整个缓冲区为空格
    FillConsoleOutputCharacter(hConsole, ' ', cells, topLeft, &written);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cells, topLeft, &written);

    // 移动光标到左上角
    SetConsoleCursorPosition(hConsole, topLeft);
}

void fillScreenWithBlank() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    // 获取控制台宽度
    int consoleWidth = csbi.dwSize.X;
    for (int i = 0; i < consoleWidth; i++) {
        putchar(' ');
    }
    putchar('\n');
}

/**
 * @brief 设置文字颜色
 * 
 * @param x 颜色代码
 */
void color(int x) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

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
    // cls;
    clearScreen(); // 更新界面，windows为"cls"，linux为""

    printf("\n=================================================================\n");
    printf("当前棋盘上的棋子：\n");
    for (int i = 0, len = 0; i <= board->objects->top; i++, len++)
    {
        if (len >= 8) {
            len = 0;
            putchar('\n');
        }
        autoColor_printf(board->objects->stack[i]->owner, "%s(%d)\t", chessName(board->objects->stack[i]), i);
    }
    printf("\n=================================================================\n");

    printf("  ");
    for (int i = 0; i < BOARD_COL; i++)
    {
        printf("%d  ", i);
    }
    putchar('\n');  
    
    for (int i = 0; i < BOARD_ROW; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < BOARD_COL; j++)
        {
            if(isEmptyBlock(board, i, j)) {
                if (isMoveable(board, i, j)) {
                    printf("++");
                }
                else {
                    printf("**");
                }
            }
            else {
                struct Chess *piece = getChessByPos(board, i, j);
                const char* name = chessName(piece);
                if (piece == getChessChoose(board)) {
                    color_printf(BLUE_TEXT, "%s", name);
                } else if (isAttackable(board, i, j)) {
                    color_printf(YELLOW_TEXT, "%s", name);
                } else {
                    autoColor_printf(piece->owner, "%s", name);
                }
            }
            putchar(' ');
        }
        putchar('\n');
    }

    // 打印玩家击败的棋子
    for (int i = 0; i < 2; i++)
    {
        printf("%s\t", c2tUser(board, i));
        for (int j = 0; j <= board->dead_chess[1-i]->top; j++)
        {
            autoColor_printf(1-i, "%s ", chessName(board->dead_chess[1-i]->stack[j]));
        }
        putchar('\n');
    }
    
    // 提示当前操作玩家及其颜色
    printf("当前操作玩家：");
    autoColor_printf(board->user, "%s", c2tUser(board, board->user));
    fillScreenWithBlank();

    // 提示玩家当前选中棋子及其战斗属性
    printf("当前选中棋子：");
    if (board->chessChoose == NULL) {
        printf("未选中棋子");
    } else {
        autoColor_printf(board->chessChoose->owner, "%s", chessName(board->chessChoose));
        printChessBattleProperty(board->chessChoose);
    }
    fillScreenWithBlank();
    if (board->tip->top == -1) {
        fillScreenWithBlank();
        fillScreenWithBlank();
    }

    // 提示操作结果或者错误
    for (int i = 0; i <= board->tip->top; i++)
    {
        printf("%s", board->tip->strs[board->tip->top]);
        fillScreenWithBlank();
    }
    board->tip->top = -1;
    Sleep(NORMAL_INTERVAL);
}