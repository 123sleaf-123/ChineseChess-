#include "chess.h"

Chess initChess(struct ChessBoard *board, int type, int owner, int isAlive) {
    struct Chess* ch = (Chess) malloc(sizeof(struct Chess));
    ch->id = board->objectCount;
    ch->type = type;
    ch->owner = owner;
    ch->isAlive = isAlive;
    board->objects[board->objectCount++] = ch;
    return ch;
}

struct chessStack* initChessStack() {
    struct chessStack* stk = (struct chessStack*) malloc(sizeof(struct chessStack));
    stk->top = 0;
}

struct ChessBoard* initChessBoard() {
    struct ChessBoard* board = (struct ChessBoard*) malloc(sizeof(struct ChessBoard));
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board->block[i][j] = NULL;
        }
    }
    board->objectCount = 0;

    // ���һ��ʼ��
    board->block[9][4] = initChess(board, GENERAL, PLAYER_1, true);

    board->block[9][3] = initChess(board, WARRIOR, PLAYER_1, true);
    board->block[9][5] = initChess(board, WARRIOR, PLAYER_1, true);

    
    board->block[9][2] = initChess(board, ELEPHANT, PLAYER_1, true);
    board->block[9][6] = initChess(board, ELEPHANT, PLAYER_1, true);

    
    board->block[9][1] = initChess(board, HORSE, PLAYER_1, true);
    board->block[9][7] = initChess(board, HORSE, PLAYER_1, true);

    
    board->block[9][0] = initChess(board, CHARIOT, PLAYER_1, true);
    board->block[9][8] = initChess(board, CHARIOT, PLAYER_1, true);

    
    board->block[7][1] = initChess(board, ARTILLERY, PLAYER_1, true);
    board->block[7][7] = initChess(board, ARTILLERY, PLAYER_1, true);

    board->block[6][0] = initChess(board, SOLDIER, PLAYER_1, true);
    board->block[6][2] = initChess(board, SOLDIER, PLAYER_1, true);
    board->block[6][4] = initChess(board, SOLDIER, PLAYER_1, true);
    board->block[6][6] = initChess(board, SOLDIER, PLAYER_1, true);
    board->block[6][8] = initChess(board, SOLDIER, PLAYER_1, true);

    // ��Ҷ���ʼ��
    board->block[0][4] = initChess(board, GENERAL, PLAYER_2, true);

    board->block[0][3] = initChess(board, WARRIOR, PLAYER_2, true);
    board->block[0][5] = initChess(board, WARRIOR, PLAYER_2, true);

    
    board->block[0][2] = initChess(board, ELEPHANT, PLAYER_2, true);
    board->block[0][6] = initChess(board, ELEPHANT, PLAYER_2, true);

    
    board->block[0][1] = initChess(board, HORSE, PLAYER_2, true);
    board->block[0][7] = initChess(board, HORSE, PLAYER_2, true);

    
    board->block[0][0] = initChess(board, CHARIOT, PLAYER_2, true);
    board->block[0][8] = initChess(board, CHARIOT, PLAYER_2, true);

    
    board->block[2][1] = initChess(board, ARTILLERY, PLAYER_2, true);
    board->block[2][7] = initChess(board, ARTILLERY, PLAYER_2, true);

    board->block[3][0] = initChess(board, SOLDIER, PLAYER_2, true);
    board->block[3][2] = initChess(board, SOLDIER, PLAYER_2, true);
    board->block[3][4] = initChess(board, SOLDIER, PLAYER_2, true);
    board->block[3][6] = initChess(board, SOLDIER, PLAYER_2, true);
    board->block[3][8] = initChess(board, SOLDIER, PLAYER_2, true);
    
    // ���ƶ������ʼ��
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board->moveablePos[i][j] = false;
        } 
    }
    
    board->user = PLAYER_1; // ������ҳ�ʼ��
    board->dead_player1 = initChessStack();
    board->dead_player2 = initChessStack();
}

int setChessBoardMoveablePos(struct ChessBoard *board, int row, int col, int val) {
    if ((0 <= row && row <= 9) && (0 <= col && col <= 8)) {
        board->moveablePos[row][col] = val;
        return true;
    }
    else return false;
}

struct Position* initPosition(int x, int y) {
    struct Position* pos = (struct Position*) malloc(sizeof(struct Position));
    pos->x = x;
    pos->y = y;
    return pos;
}

/**
 * @brief ����������ɫ
 * 
 * @param x ��ɫ����
 */
void color(int x) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

char *c2tUser(struct ChessBoard* board, int code) {
    if (code == PLAYER_1) return "���һ";
    if (code == PLAYER_2) return "��Ҷ�";
    return "";
}

/**
 * @brief �������ӣ���������������֣��������
 * 
 * @param chess �������
 * @return char* ������������
 */
char *chessName(struct Chess* chess) {
    switch(chess->owner) {
        // ���һ�Ǻ�ɫ
        case PLAYER_1: {
            switch(chess->type) {
                case GENERAL: return "��";
                case CHARIOT: return "�e";
                case HORSE: return "��";
                case ARTILLERY: return "��";
                case ELEPHANT: return "��";
                case WARRIOR: return "��";
                case SOLDIER: return "��";
            }
            break;
        }

        // ��Ҷ�����ɫ
        case PLAYER_2: {
            switch(chess->type) {
                case GENERAL: return "��";
                case CHARIOT: return "܇";
                case HORSE: return "�R";
                case ARTILLERY: return "�h";
                case ELEPHANT: return "��";
                case WARRIOR: return "ʿ";
                case SOLDIER: return "��";
            }
            break;
        }
    }

    return " ";
}

void actionFinished(struct ChessBoard *board) {
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board->moveablePos[i][j] = false;
        } 
    }
}

/*
    1.�����ƶ���
        1.1. ԭλ�ò����ڼ������ӻ򲻴�������
        1.2. Ŀ��λ�ó������̷�Χ
        1.3. Ŀ��λ�ô��ڼ�������
        1.4. �����������ƶ�����
    2. ���ƶ��������˼������ӣ�δ�������̷�Χ���ҷ����ƶ�������Ŀ��λ�ò����ڼ�������
        2.1. ��ɱ
        2.2. �޻�ɱ
*/

/**
 * @brief �Ƿ񳬳����̷�Χ
 * 
 * @param row Ŀ����
 * @param col Ŀ����
 * @return int ����false����Ŀ��λ�ó������̣����򣬷���true
 */
int isInside(int row, int col) {
    return (row < BOARD_ROW) && (col < BOARD_COL) && (row >= 0) && (col >= 0);
}

/**
 * @brief ��ǰ����λ���Ƿ��������
 * 
 * @param board ����
 * @param row ��
 * @param col ��
 * @return int ����true�������������ӣ�����false������������
 */
int isNull(struct ChessBoard* board, int row, int col) {
    return board->block[row][col] == NULL;
}

/**
 * @brief ԭλ���Ƿ���ڼ�������
 * 
 * @param board ����
 * @param row ԭ��
 * @param col ԭ��
 * @return int ����true�������ڼ������ӣ�����false�������������ӻ���ڵз�����
 */
int isControllable(struct ChessBoard* board, int row, int col) {
    return !isNull(board, row, col) && (board->block[row][col]->owner == board->user);
}

/**
 * @brief Ŀ��λ���Ƿ���ڼ������ӣ��Ƿ���������
 * 
 * @param board ����
 * @param row Ŀ����
 * @param col Ŀ����
 * @return int ����true����Ŀ��λ��Ϊ�ҷ����ӣ�����false����Ŀ��λ��Ϊ�ջ�з�����
 */
int friendlyFireDetect(struct ChessBoard* board, int row, int col) {
    return !isNull(board, row, col) 
    && (board->block[row][col]->owner == board->user);
}

/**
 * @brief λ���Ƿ����������ڣ����һ�������5-9�У���Ҷ��������0-4��
 * ʹ��ǰ�����ʹ��isInside()
 * 
 * @param board ����
 * @param row 
 * @param col 
 * @return int ����true������Ҳ����Լ�������ڣ����򷵻�false
 */
int isBeyond(struct ChessBoard* board, int row, int col) {
    if (board->user == PLAYER_1) 
        return !((5 <= row && row <= 9) && (0 <= col && col <= 8));
    if (board->user == PLAYER_2) 
        return !((0 <= row && row <= 4) && (0 <= col && col <= 8));
}

int isInsidePalace(struct ChessBoard* board, int row, int col) {
    if (board->user == PLAYER_1) 
        return (7 <= row) && (row <= 9) && (3 <= col) && (col <= 5);
    if (board->user == PLAYER_2) 
        return (0 <= row) && (row <= 2) && (3 <= col) && (col <= 5);
}

/**
 * @brief ѡ�����ӣ������Բ��ݣ����������ƶ�·��ͼ��
 * 
 * @param board ����
 * @param src_row 
 * @param src_col 
 * @return int ����true�������ӿ��Բ��ݣ����򣬷���false
 */
int choose(struct ChessBoard* board, int src_row, int src_col) {
    if (isControllable(board, src_row, src_col) == false) 
        return false;
    else {
        moveablePosition(board, src_row, src_col); 
        return true;
    }
}

void moveablePosition(struct ChessBoard* board, int src_row, int src_col) {
    struct Chess* chess = board->block[src_row][src_col];
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board->moveablePos[i][j] = false;
        } 
    }
    
    switch (chess->type) {
        case GENERAL: // �Ƿ��ھŹ��������ƶ���һ��
        {
            int dest_row[4], dest_col[4], inside;
            dest_row[0] = src_row + 1;
            dest_row[1] = src_row;
            dest_row[2] = src_row - 1;
            dest_row[3] = src_row;
            dest_col[0] = src_col;
            dest_col[1] = src_col + 1;
            dest_col[2] = src_col;
            dest_col[3] = src_col - 1;
            for (int i = 0; i < 4; i++)
            {
                if (isInsidePalace(board, dest_row[i], dest_col[i]) == true) 
                    board->moveablePos[dest_row[i]][dest_col[i]] = true;
            }
            break;
        }
        case CHARIOT: // ����Ŀ��λ����Դλ���Ƿ���ͬһ�л�ͬһ��
        {
            for (int i = src_row+1, j = src_col; isInside(i, j) && isNull(board, i, j); ++i) {
                board->moveablePos[i][j] = true;
            }
            for (int i = src_row-1, j = src_col; isInside(i, j) && isNull(board, i, j); --i) {
                board->moveablePos[i][j] = true;
            }
            for (int i = src_row, j = src_col+1; isInside(i, j) && isNull(board, i, j); ++j) {
                board->moveablePos[i][j] = true;
            }
            for (int i = src_row, j = src_col-1; isInside(i, j) && isNull(board, i, j); --j) {
                board->moveablePos[i][j] = true;
            }
            break;
        }
        case HORSE: // ��
        {
            int dest_row[4], dest_col[4];
            dest_row[0] = src_row + 1;
            dest_row[1] = src_row;
            dest_row[2] = src_row - 1;
            dest_row[3] = src_row;
            dest_col[0] = src_col;
            dest_col[1] = src_col + 1;
            dest_col[2] = src_col;
            dest_col[3] = src_col - 1;
            for (int i = 0; i < 4; i++)
            {
                if (isInside(dest_row[i], dest_col[i]) && isNull(board, dest_row[i], dest_col[i])) {
                    if (i == 0) {
                        // ��
                        setChessBoardMoveablePos(board, dest_row[i] + 1, dest_col[i] - 1, true);
                        setChessBoardMoveablePos(board, dest_row[i] + 1, dest_col[i] + 1, true);
                    }
                    if (i == 1) {
                        // ��
                        setChessBoardMoveablePos(board, dest_row[i] + 1, dest_col[i] + 1, true);
                        setChessBoardMoveablePos(board, dest_row[i] - 1, dest_col[i] + 1, true);
                    }
                    if (i == 2) {
                        // ��
                        setChessBoardMoveablePos(board, dest_row[i] - 1, dest_col[i] + 1, true);
                        setChessBoardMoveablePos(board, dest_row[i] - 1, dest_col[i] - 1, true);
                    }
                    if (i == 3) {
                        // ��
                        setChessBoardMoveablePos(board, dest_row[i] + 1, dest_col[i] - 1, true);
                        setChessBoardMoveablePos(board, dest_row[i] - 1, dest_col[i] - 1, true);
                    }
                }
            }
            
            break;
        }
        case ARTILLERY: 
            // Ŀ��λ����Դλ���Ƿ���ͬһ�л�ͬһ��
            // ��Ŀ��λ���е��ˣ�Ŀ��λ����Դλ��֮���Ƿ�������
        {
            int i, j;
            for (i = src_row+1, j = src_col; isInside(i, j) && isNull(board, i, j); ++i) {
                board->moveablePos[i][j] = true;
            }
            for (++i; isInside(i, j); ++i) {
                if (!isNull(board, i, j)) {
                    if (!friendlyFireDetect(board, i, j)) board->moveablePos[i][j] = true;
                    break;
                }
            }
            for (i = src_row-1, j = src_col; isInside(i, j) && isNull(board, i, j); --i) {
                board->moveablePos[i][j] = true;
            }
            for (--i; isInside(i, j); --i) {
                if (!isNull(board, i, j)) {
                    if (!friendlyFireDetect(board, i, j)) board->moveablePos[i][j] = true;
                    break;
                }
            }
            for (i = src_row, j = src_col+1; isInside(i, j) && isNull(board, i, j); ++j) {
                board->moveablePos[i][j] = true;
            }
            for (++j; isInside(i, j); ++j) {
                if (!isNull(board, i, j)) {
                    if (!friendlyFireDetect(board, i, j)) board->moveablePos[i][j] = true;
                    break;
                }
            }
            for (i = src_row, j = src_col-1; isInside(i, j) && isNull(board, i, j); --j) {
                board->moveablePos[i][j] = true;
            }
            for (--j; isInside(i, j); --j) {
                if (!isNull(board, i, j)) {
                    if (!friendlyFireDetect(board, i, j)) board->moveablePos[i][j] = true;
                    break;
                }
            }
            break;
        }
        case ELEPHANT: 
        {
            // ���ڲ���·����û�е���
            char stop[4] = {false, false, false, false};
            for (int i = 1; i <= 2; i++)
            {
                // ���½ǣ����½ǣ����Ͻǣ����Ͻ�
                int 
                dest_row[4] = { src_row + i, src_row + i, src_row - i, src_row - i }, 
                dest_col[4] = { src_col + i, src_col - i, src_col - i, src_col + i }; 
                for (int j = 0; j < 4; j++)
                {
                    // ���λ�ò��������ڡ�Խ������������赲���ۣ���ֹͣǰ��Ԥ��
                    // �������Ϊ��ǰ��
                    if (i == 1 && (isBeyond(board, dest_row[j], dest_col[j]) || !isNull(board, dest_row[j], dest_col[j]))) 
                        stop[j] = true;
                    if (i == 2 && stop[j] == false) {
                        setChessBoardMoveablePos(board, dest_row[j], dest_col[j], true);
                    }
                }
            }
            break;
        }
        case WARRIOR:
        {
            // ���½ǣ����½ǣ����Ͻǣ����Ͻ�
            int 
            dest_row[4] = { src_row + 1, src_row + 1, src_row - 1, src_row - 1 }, 
            dest_col[4] = { src_col + 1, src_col - 1, src_col - 1, src_col + 1 }; 
            for (int i = 0; i < 4; i++)
            {
                if (isInsidePalace(board, dest_row[i], dest_col[i])) {
                    setChessBoardMoveablePos(board, dest_row[i], dest_col[i], true);
                }
            }
            break;
        }
        case SOLDIER:
        {
            if (isInside(src_row, src_col) && isBeyond(board, src_row, src_col)) {
                // Խ����أ����Ӻ��磩��������������
                setChessBoardMoveablePos(board, src_row, src_col + 1, true);
                setChessBoardMoveablePos(board, src_row, src_col - 1, true);
            }
            // ���ۺ�ʱ��������ǰ�ߣ���ǰҲû���������
            if (board->user == PLAYER_1) 
                setChessBoardMoveablePos(board, src_row - 1, src_col, true);
            if (board->user == PLAYER_2) 
                setChessBoardMoveablePos(board, src_row + 1, src_col, true);
            break;
        }
    }
}

// �Ƿ���������ƶ�����
int isMoveable(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col) {
    return board->moveablePos[dest_row][dest_col] == true;
}

int action(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col) {
    // if (isControllable(board, src_row, src_col)) {
    if (isInside(dest_row, dest_col)) {
        if (!friendlyFireDetect(board, dest_row, dest_col)) {
            if (isMoveable(board, src_row, src_col, dest_row, dest_col)) {
                if (!isNull(board, dest_row, dest_col) 
                && board->block[dest_row][dest_col]->owner != board->user) {
                    struct chessStack *cstk;
                    struct Chess *dead = board->block[dest_row][dest_col];
                    if (board->block[dest_row][dest_col]->owner == PLAYER_1) {
                        cstk = board->dead_player1;
                        // printf("���һ��%d�Ѿ���������", dead->type);
                    }
                    else {
                        cstk = board->dead_player2;
                    }
                    printf("%s��%s�Ѿ���������", c2tUser(board, dead->owner), chessName(dead));
                    cstk->stack[cstk->top++] = dead;
                    getchar();
                    getchar();
                }
                board->block[dest_row][dest_col] = board->block[src_row][src_col];
                board->block[src_row][src_col] = NULL;
                return true;
            }
        }
    }
    // }
    system("cls");
    printf("�����ƶ�������");
    getchar();
    getchar();
    return false;
}


void printChessBoard(struct ChessBoard* board) {
    system("cls"); // ���½��棬windowsΪ"cls"��linuxΪ""
    printf("  ");
    for (int i = 0; i < 9; i++)
    {
        printf("%d  ", i);
    }
    putchar('\n');  
    // putchar('\n');
    
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < 9; j++)
        {
            if(board->block[i][j] == NULL) {
                if (board->moveablePos != NULL && board->moveablePos[i][j] == true) {
                    color(WHITE_TEXT);
                    printf("++");
                }
                else {
                    color(WHITE_TEXT);
                    printf("**");
                }
            }
            else {
                if (board->block[i][j]->owner == PLAYER_1) color(RED_TEXT);
                if (board->block[i][j]->owner == PLAYER_2) color(GREEN_TEXT);
                // printf("%d", board->block[i][j]->type);
                printf("%s", chessName(board->block[i][j]));
            }
            putchar(' ');
        }
        color(WHITE_TEXT);
        putchar('\n');
    }

    // ��ӡ��������
    printf("���һ\t");
    for (int i = 0; i < board->dead_player2->top; i++)
    {
        printf("%s ", chessName(board->dead_player2->stack[i]));
    }

    putchar('\n');
    printf("��Ҷ�\t");
    for (int i = 0; i < board->dead_player1->top; i++)
    {
        printf("%s ", chessName(board->dead_player1->stack[i]));
    }
    putchar('\n');

    // ��ʾ��ǰ������Ҽ�����ɫ
    printf("��ǰ������ң�");
    if (board->user == PLAYER_1) color(RED_TEXT);
    if (board->user == PLAYER_2) color(GREEN_TEXT);
    printf("%s\n", c2tUser(board, board->user));
    color(WHITE_TEXT);
}
