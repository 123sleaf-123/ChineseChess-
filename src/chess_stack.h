#ifndef CHESS_STACK_H
#define CHESS_STACK_H

// 堆放棋子的栈

struct ChessStack
{
    struct Chess **stack;
    int top;
    int maxSize;
};

struct ChessStack *initChessStack(int maxSize);
struct ChessStack *initChessStack_default();
int chessStackPush(struct ChessStack *stack, struct Chess *chess);
int isChessStackEmpty(struct ChessStack *stack);
struct Chess *chessStackTop(struct ChessStack *stack);
void chessStackPop(struct ChessStack *stack);

#endif