#ifndef CHESS_RECORD_H
#define CHESS_RECORD_H

#include "chess.h"

// 定义操作类型
typedef enum {
    OP_MOVE,    // 移动
    OP_ATTACK,   // 攻击
    OP_SKILL,    // 使用技能
    OP_SPAWN,    // 生成棋子
    OP_DEATH     // 棋子死亡
} OperationType;

// 定义操作记录结构
typedef struct {
    OperationType type;
    int src_row, src_col;    // 源位置
    int dest_row, dest_col;  // 目标位置
    struct Chess *chess;     // 相关棋子
    void *data;              // 附加数据(如技能数据、伤害值等)
} OperationRecord;

// 定义记录栈
typedef struct {
    OperationRecord **records;  // 记录数组
    OperationRecord *emptyRecord;  // 记录数组
    int capacity;              // 容量
    int top;                   // 栈顶指针
} RecordStack;

RecordStack *initRecordStack(int capacity);
OperationRecord *initOperationRecord(OperationType type, int src_row, int src_col, int dest_row, int dest_col, struct Chess *chess, void *data);
void pushRecord(RecordStack *stack, OperationRecord *record);
bool isRecordStackEmpty(RecordStack *stack);
OperationRecord *popRecord(RecordStack *stack);
void freeRecordStack(RecordStack *stack);
void printOperationRecord(const OperationRecord *record);
void printRecordStack(const RecordStack *stack);

#endif