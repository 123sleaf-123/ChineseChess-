#include "chess_record.h" 

RecordStack *initRecordStack(int capacity) {
    RecordStack *stack = (RecordStack *)malloc(sizeof(RecordStack));
    stack->records = (OperationRecord *)malloc(sizeof(OperationRecord) * capacity);
    stack->capacity = capacity;
    stack->top = -1;
    return stack;
}

bool isRecordStackEmpty(RecordStack *stack) {
    return stack->top == -1;
}

void pushRecord(RecordStack *stack, OperationRecord record) {
    if (stack->top >= stack->capacity - 1) {
        // 扩容
        stack->capacity *= 2;
        stack->records = (OperationRecord *)realloc(stack->records, sizeof(OperationRecord) * stack->capacity);
    }
    stack->records[++stack->top] = record;
}

OperationRecord popRecord(RecordStack *stack) {
    if (stack->top < 0) {
        OperationRecord empty = {0};
        return empty;
    }
    return stack->records[stack->top--];
}

void freeRecordStack(RecordStack *stack) {
    free(stack->records);
    stack->records = NULL;
    stack->capacity = 0;
    stack->top = -1;
}