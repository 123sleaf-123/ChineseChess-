#include "chess_record.h" 

RecordStack *initRecordStack(int capacity) {
    RecordStack *stack = (RecordStack *)malloc(sizeof(RecordStack));
    stack->records = (OperationRecord *)malloc(sizeof(OperationRecord) * capacity);
    stack->emptyRecord = (OperationRecord *)malloc(sizeof(OperationRecord));
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

OperationRecord *popRecord(RecordStack *stack) {
    if (stack->top < 0) {
        return stack->emptyRecord; // 返回空记录
    }
    return &stack->records[stack->top--];
}

void freeRecordStack(RecordStack *stack) {
    free(stack->records);
    stack->records = NULL;
    stack->capacity = 0;
    stack->top = -1;
}

void printOperationRecord(const OperationRecord *record) {
    if (record == NULL) {
        printf("NULL OperationRecord\n");
        return;
    }

    printf("OperationRecord {\n");
    printf("  type: %d\n", record->type);
    printf("  src: (%d, %d)\n", record->src_row, record->src_col);
    printf("  dest: (%d, %d)\n", record->dest_row, record->dest_col);
    printf("  chess: %p\n", (void*)record->chess);
    printf("  data: %p\n", record->data);
    printf("}\n");
}

void printRecordStack(const RecordStack *stack) {
    if (stack == NULL) {
        printf("NULL RecordStack\n");
        return;
    }

    printf("RecordStack {\n");
    printf("  capacity: %d\n", stack->capacity);
    printf("  top: %d\n", stack->top);
    printf("  records: [\n");
    
    for (int i = 0; i <= stack->top; i++) {
        printf("    %d: ", i);
        printOperationRecord(&stack->records[i]);
    }
    
    printf("  ]\n");
    printf("  emptyRecord: ");
    printOperationRecord(stack->emptyRecord);
    printf("}\n");
}