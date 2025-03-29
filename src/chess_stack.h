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
int ChessStackPush(struct ChessStack *stack, struct Chess *chess);
int isChessStackEmpty(struct ChessStack *stack);
struct Chess *ChessStackTop(struct ChessStack *stack);
void ChessStackPop(struct ChessStack *stack);

#endif