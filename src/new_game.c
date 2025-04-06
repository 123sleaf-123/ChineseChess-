#include "new_game.h"
#include "chess.h"
#include "chess_board.h"


// #define INTERVAL NORMAL_INTERVAL
#define INTERVAL SHORT_INTERVAL
#define BREAK 100
#define CONTINUE 101

/**
 * 玩家控制可以分为几个阶段：
 * 1. 第一阶段：
 *      1.1. 选中 棋子 —— 第二阶段
 *      1.2. 回退 操作/指令 —— 继续循环
 *      1.3. 退出 —— 结束循环
 * 2. 第二阶段：
 *      2.1. 移动 棋子 —— 第三阶段
 *      2.2. 取消选中 —— 继续循环
 * 3. 第三阶段：
 *      3.1. 选择作用方式（装备、技能） —— 第四阶段
 *      3.2. 取消移动 —— 第二阶段
 * 4. 第四阶段：
 *      4.1. 选择作用棋子 —— 第五阶段
 *      4.2. 取消作用方式选择 —— 第三阶段
 * 5. 第五阶段：
 *      5.1. 进入战斗 —— 结束
 */
int userControl(struct ChessBoard *board, bool *res) {
    char input[10];
    int stage = 1;  // Start at stage 1
    int src_row, src_col, dest_row, dest_col, target_row, target_col;
    struct Chess *chessChoose = NULL;
    
    while (stage <= 5) {
        printChessBoard(board);
        scanf("%s", input);

        switch (stage) {
            case 1:  // Selection stage
                if (strcmp(input, "q") == 0) {
                    cls;
                    for (int i = 0; i < 5; i++) {
                        printf("伊蕾娜正在构建主界面中");
                        for (int j = 0; j < 3; j++) {
                            putchar('.');
                            Sleep(500);
                        }
                        cls;
                    }
                    Sleep(INTERVAL);
                    return BREAK;
                }
                if (strcmp(input, "w") == 0) {
                    cls;
                    printf("伊蕾娜不喜欢刚才做的决定...\n");
                    Sleep(INTERVAL);
                    printf("天才美少女魔女伊蕾娜正在使用魔法...\n");
                    Sleep(INTERVAL);
                    printf("败者食尘！\n");
                    withdraw(board);
                    withdraw(board);
                    Sleep(INTERVAL);
                    return CONTINUE;
                }
                src_row = input[0] - '0';
                src_col = input[1] - '0';
                if (choose(board, src_row, src_col)) {
                    stage = 2;
                }
                break;

            case 2:  // Movement stage
                if (strcmp(input, "cancel") == 0) {
                    // actionFinished(board);
                    stage = 1;
                }
                dest_row = input[0] - '0';
                dest_col = input[1] - '0';
                if (moveChess(board, src_row, src_col, dest_row, dest_col)) {
                    stage = 3;
                }
                break;
            case 3: // Action selection stage
                chessChoose = getChessChoose(board);
                if (strcmp(input, "cancel") == 0) {
                    withdraw(board);
                    stage = 2;
                    continue;
                }
                else if (strcmp(input, "bow") == 0) {
                    setChessMinRange(chessChoose, 2);
                    setChessMaxRange(chessChoose, 2);
                    attackablePosition(board, dest_row, dest_col);
                    stage = 4;
                }
                else if (strcmp(input, "sword") == 0) {
                    setChessMinRange(chessChoose, 1);
                    setChessMaxRange(chessChoose, 1);
                    attackablePosition(board, dest_row, dest_col);
                    stage = 4;
                } else if (strcmp(input, "fin") == 0) {
                    actionFinished(board);
                    *res = true;
                    return true;
                }
                break;
            case 4:  // Target selection stage
                if (strcmp(input, "cancel") == 0) {
                    resetAttackablePos(board);
                    stage = 3;
                    continue;
                }
                target_row = input[0] - '0';
                target_col = input[1] - '0';
                setChessTobeOperated(board, getChessByPos(board, target_row, target_col));
                stage = 5;
                break;

            case 5:  // Combat stage
                if (strcmp(input, "cancel") == 0) {
                    stage = 4;
                    continue;
                }
                dest_row = input[0] - '0';
                dest_col = input[1] - '0';
                if (fight(board, getChessChoose(board), getChessTobeOperated(board))) {
                    *res = true;
                    return true;
                }
                break;
        }
    }
    return CONTINUE;
}

int aiControl(struct ChessBoard *board, bool *res)
{
    int dest_row, dest_col;
    aiLogic(board, &dest_row, &dest_col);
}

void initChessGame()
{
    // 初始化棋盘
    Board board;
    board = initChessBoard();
    while (true)
    {
        // 待选择阶段
        printChessBoard(board);
        bool action_res;

        // 移动阶段
        bool isBreak = userControl(board, &action_res);
        if (isBreak == BREAK) break;
        if (isBreak == CONTINUE) continue;

        // 结束阶段，不需要输入
        printChessBoard(board);
        actionFinished(board);
        if (action_res == true)
        {
            // 如果玩家已经行动
            if (isGameEnd(board) == true)
            {
                printChessBoard(board);
                putchar('\n');
                printf("游戏结束");
                Sleep(NORMAL_INTERVAL);
                break;
            }
            else
                board->user = !board->user;
        }
    }
    // getchar();
}

