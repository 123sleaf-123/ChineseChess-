#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define true 1
#define false 0
#define BOARD_ROW 10
#define BOARD_COL 9

typedef struct Chess
{
    int type;
    int owner; // 
    int isAlive;
} *Chess;

// block type
#define EMPTY 0
#define GENERAL 1 // ��/˧
#define CHARIOT 2 // ��
#define HORSE 3 // ��
#define ARTILLERY 4 // ��
#define ELEPHANT 5 // ��/��
#define WARRIOR 6 // ʿ/��
#define SOLIDER 7 // ��

// owner
#define PLAYER_1 0
#define PLAYER_2 1
#define SPARE 3

// isAlive
#define DEAD false
#define ALIVE true

Chess initChess(int type, int owner, int isAlive);
Chess initChess(int type, int owner, int isAlive) {
    struct Chess* ch = (Chess) malloc(sizeof(struct Chess));
    ch->type = type;
    ch->owner = owner;
    ch->isAlive = isAlive;
    return ch;
}

struct chessStack
{
    struct Chess *stack[16];
    int top;
};

struct chessStack* initChessStack() {
    struct chessStack* stk = (struct chessStack*) malloc(sizeof(struct chessStack));
    stk->top = 0;
}

typedef struct ChessBoard
{
    struct Chess *block[10][9];
    int user;
    struct chessStack *dead_player1;
    struct chessStack *dead_player2;
} *Board;

struct ChessBoard* init();
struct ChessBoard* init() {
    struct ChessBoard* board = (struct ChessBoard*) malloc(sizeof(struct ChessBoard));
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board->block[i][j] = NULL;
        }
    }

    // ���һ��ʼ��
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

    board->block[6][0] = initChess(SOLIDER, PLAYER_1, true);
    board->block[6][2] = initChess(SOLIDER, PLAYER_1, true);
    board->block[6][4] = initChess(SOLIDER, PLAYER_1, true);
    board->block[6][6] = initChess(SOLIDER, PLAYER_1, true);
    board->block[6][8] = initChess(SOLIDER, PLAYER_1, true);

    // ��Ҷ���ʼ��
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

    board->block[3][0] = initChess(SOLIDER, PLAYER_2, true);
    board->block[3][2] = initChess(SOLIDER, PLAYER_2, true);
    board->block[3][4] = initChess(SOLIDER, PLAYER_2, true);
    board->block[3][6] = initChess(SOLIDER, PLAYER_2, true);
    board->block[3][8] = initChess(SOLIDER, PLAYER_2, true);
    
    board->user = PLAYER_1;
    board->dead_player1 = initChessStack();
    board->dead_player2 = initChessStack();
}

/*
    1.�����ƶ���
        1.1. ԭλ�ò����ڼ������ӻ򲻴�������
        1.2. Ŀ��λ�ó������̷�Χ
        1.3. Ŀ��λ�ô��ڼ�������
        1.4. �����������ƶ�����
    2. ���ƶ��������˼������ӣ�δ�������̷�Χ���ҷ����ƶ�������Ŀ��λ�ò����ڼ�������
*/

// ԭλ���Ƿ�������ӣ�������Ϊ��������
int isControllable(struct ChessBoard* board, int row, int col);
int isControllable(struct ChessBoard* board, int row, int col) {
    return board->block[row][col] != NULL && board->block[row][col]->owner == board->user;
}

// �Ƿ񳬳����̷�Χ
int isInside(int row, int col); 
int isInside(int row, int col) {
    return row < BOARD_ROW && col < BOARD_COL;
}

/**
 * @brief Ŀ��λ���Ƿ���ڼ������ӣ��Ƿ���������
 * 
 * @param board ����
 * @param row Ŀ����
 * @param col Ŀ����
 * @return int ����true����Ŀ��λ��Ϊ�ҷ����ӣ�����false����Ŀ��λ��Ϊ�ջ�з�����
 */
int friendlyFireDetect(struct ChessBoard* board, int row, int col);
int friendlyFireDetect(struct ChessBoard* board, int row, int col) {
    return board->block[row][col]->owner == board->user;
}

// �Ƿ���������ƶ�����
int isMoveable(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col);
int isMoveable(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col) {
    struct Chess* chess = board->block[src_row][src_col];
    int distance_square 
    = (dest_row - src_row) * (dest_row - src_row) 
    + (dest_col - src_col) * (dest_col - src_col);
    if (distance_square == 0) return false;

    switch (chess->type) {
        case GENERAL: // �Ƿ��ھŹ��������ƶ���һ��
        {
            int inside = (dest_row >= 0) && (dest_row < 3) && (dest_col > 2) && (dest_col < 6);
            return inside && distance_square <= 2;
        }
        case CHARIOT: // Ŀ��λ����Դλ���Ƿ���ͬһ�л�ͬһ��
            return dest_row == src_row || dest_col == src_col;
        case HORSE: // �Ƿ��ƶ�������
            return distance_square <= 5;
        case ARTILLERY: 
            // Ŀ��λ����Դλ���Ƿ���ͬһ�л�ͬһ��
            // ��Ŀ��λ���е��ˣ�Ŀ��λ����Դλ��֮���Ƿ�������
            if (dest_row == src_row || dest_col == src_col) {
                if (board->block[dest_row][dest_col]->owner != board->user) {
                    if (dest_row == src_row) {
                        int begin = (src_col < dest_col ? src_col : dest_col) + 1;
                        int end = src_col < dest_col ? dest_col : src_col;
                        for (int i = begin; i < end; i++)
                        {
                            if (board->block[dest_row][i] != NULL) return true;
                        }
                        return false;
                    }
                    if (dest_col == src_col) {
                        int begin = (src_row < dest_row ? src_row : dest_row) + 1;
                        int end = src_row < dest_row ? dest_row : src_row;
                        for (int i = begin; i < end; i++)
                        {
                            if (board->block[i][dest_col] != NULL) return true;
                        }
                        return false;
                    }
                    return true;
                }
            }
            else return false;
        // case
        // case
        // case
    }
    // if (chess->type == GENERAL) {
    //     inside = dest_row >= 0 && dest_row < 3 && dest_col > 2 && dest_col < 6;
    // }
}

void action(struct ChessBoard* board);
void action(struct ChessBoard* board) {
    char src[3], dest[3];
    scanf("%s %s", src, dest);
    int 
    src_row = src[0] - '0', 
    src_col = src[1] - '0', 
    dest_row = dest[0] - '0', 
    dest_col = dest[1] - '0';

    if (src_row < BOARD_ROW && src_col < BOARD_COL 
    && board->block[src_row][src_col] != NULL 
    && dest_row < BOARD_ROW && src_col < BOARD_COL) {
        if (board->block[dest_row][dest_col] != NULL) {
            if (board->block[dest_row][dest_col]->owner == board->block[src_row][src_col]->owner) {
                system("cls");
                printf("�����ƶ�������");
                getchar();
                getchar();
                return;
            }
            else {
                struct chessStack *cstk;
                struct Chess *dead = board->block[dest_row][dest_col];
                if (board->block[dest_row][dest_col]->owner == PLAYER_1) {
                    cstk = board->dead_player1;
                    printf("���һ��%d�Ѿ���������", dead->type);
                }
                else {
                    cstk = board->dead_player2;
                    printf("��Ҷ���%d�Ѿ���������", dead->type);
                }
                cstk->stack[cstk->top++] = dead;
                getchar();
                getchar();
            }
        }
        board->block[dest_row][dest_col] = board->block[src_row][src_col];
        board->block[src_row][src_col] = NULL;
    }
    // while (getchar() != '\n'); // ��������Ҫ���ַ�
}

void printChessBoard(struct ChessBoard* board);
void printChessBoard(struct ChessBoard* board) {
    printf("  ");
    for (int i = 0; i < 9; i++)
    {
        printf("%d", i);
    }
    putchar('\n');  putchar('\n');
    
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < 9; j++)
        {
            if(board->block[i][j] == NULL) printf("*");
            else {
                // if (board->block[i][j]->type == GENERAL 
                // && board->block[i][j]->owner == PLAYER_1 
                // && board->block[i][j]->isAlive == true) printf("��");
                // else 
                printf("%d", board->block[i][j]->type);
            }
        }
        putchar('\n');
    }

    // ��ӡ��������
    printf("���һ\t");
    for (int i = 0; i < board->dead_player2->top; i++)
    {
        printf("%d ", board->dead_player2->stack[i]->type);
    }

    putchar('\n');
    printf("��Ҷ�\t");
    for (int i = 0; i < board->dead_player1->top; i++)
    {
        printf("%d ", board->dead_player1->stack[i]->type);
    }
    putchar('\n');
}

int main(int argc, char const *argv[])
{   
    // ��ʼ������
    Board board;
    board = init();
    while(true) {
        printChessBoard(board);
        action(board);
        board->user = !board->user;
        system("cls"); // ���½��棬windowsΪ"cls"��linuxΪ""
    // printChessBoard(board);
    }
    // while(true) ;
    getchar();
    return 0;
}
