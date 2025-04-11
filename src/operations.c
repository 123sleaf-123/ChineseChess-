#include "operations.h"

/*
    1.不可移动：
        1.1. 原位置不存在己方棋子或不存在棋子
        1.2. 目标位置超出棋盘范围
        1.3. 目标位置存在棋子
        1.4. 超出移动范围
        1.5. 目标位置无法进入
    2. 可移动：操纵了己方棋子，未超出棋盘范围，且符合移动规则，且目标位置不存在己方棋子
        2.1. 击杀
        2.2. 无击杀
*/

/**
 * @brief 选择棋子，若可以操纵，则记录当前选中棋子，计算出可移动路径图层
 *
 * @param board 棋盘
 * @param src_row
 * @param src_col
 * @return int 返回true，若棋子可以操纵；否则，返回false
 */
int choose(struct ChessBoard *board, int src_row, int src_col)
{
    if (isControllable(board, src_row, src_col) == false)
        return false;
    else
    {
        board->chessChoose = board->block[src_row][src_col];
        moveablePosition(board, src_row, src_col);
        return true;
    }
}

int moveChess(struct ChessBoard *board, int src_row, int src_col, int dest_row, int dest_col) {
    if (src_row == dest_row && src_col == dest_col) {
        return true;
    }
    RecordStack *record_stack = getRecordStack(board);
    if (isInside(dest_row, dest_col) && isMoveable(board, dest_row, dest_col)) {
        // 创建移动记录
        OperationRecord *moveRecord = initOperationRecord(OP_MOVE, src_row, src_col, dest_row, dest_col, board->block[src_row][src_col], NULL);
        pushRecord(record_stack, moveRecord);

        // 执行移动
        setChessBoardBlock(board, dest_row, dest_col, board->block[src_row][src_col]);
        setChessBoardBlock(board, src_row, src_col, NULL);
        return true;
    }
    sprintf(board->tip->strs[++board->tip->top], "不可移动到这里");
    return false;
}

bool withdraw(struct ChessBoard *board) {
    RecordStack *record_stack = getRecordStack(board);
    if (isRecordStackEmpty(record_stack))
        return false;
    
    OperationRecord *record = popRecord(record_stack);
    
    switch (record->type) {
        case OP_MOVE: {
            // 撤销移动：将棋子移回原位置
            struct Chess *chess = record->chess;
            setChessBoardBlock(board, record->src_row, record->src_col, chess);
            setChessBoardBlock(board, record->dest_row, record->dest_col, NULL);
            break;
        }
        case OP_ATTACK: {
            // 撤销攻击：恢复生命值
            int damage = (int)(intptr_t)record->data;
            recoverChess(record->chess, damage);
            break;
        }
        case OP_DEATH: {
            // 撤销死亡：复活棋子
            int damage = (int)(intptr_t)record->data;
            recoverChess(record->chess, damage);
            
            // 从死亡栈中移除
            chessStackPop(board->dead_chess[record->chess->owner]);
            break;
        }
        // 其他操作类型的处理...
        default:
            break;
    }
    
    return true;
}

int fight(struct ChessBoard* board, struct Chess *attacker, struct Chess *defender) {
    if (attacker == NULL || defender == NULL) {
        sprintf(board->tip->strs[++board->tip->top], "攻击者或防御者不存在");
        return false;
    }
    if (!isInsideAttackRangeByChess(attacker, defender)) {
        sprintf(board->tip->strs[++board->tip->top], "目标不在攻击范围内");
        return false;
    }

    int attack = getAttack(getChessBattleProperty(attacker));
    int defense = getDefense(getChessBattleProperty(defender));
    int damage = attack - defense;
    if (damage < 0) damage = 0;
    
    // 打印攻击信息
    sprintf(board->tip->strs[++board->tip->top],
            "Attack: %s(ATK:%d) -> %s(DEF:%d), Damage:%d\n", 
           chessName(attacker),
           attack,
           chessName(defender),
           defense,
           damage);
    
    // 创建攻击记录
    OperationRecord *attackRecord = initOperationRecord(OP_ATTACK, 0, 0, 0, 0, attacker, (void *)(intptr_t)damage);
    pushRecord(getRecordStack(board), attackRecord);
    
    takeDamageChess(defender, damage);
    
    if (getHealth(getChessBattleProperty(defender)) <= 0) {
        defender->is_alive = false;
        
        // 创建死亡记录
        OperationRecord *deathRecord = initOperationRecord(OP_DEATH, 0, 0, 0, 0, defender, (void *)(intptr_t)damage);
        pushRecord(getRecordStack(board), deathRecord);
    }
    return true;
}

int fightByPos(struct ChessBoard* board, int src_row, int src_col, int dest_row, int dest_col) {
    struct Chess *attacker = getChessByPos(board, src_row, src_col);
    struct Chess *defender = getChessByPos(board, dest_row, dest_col);
    return fight(board, attacker, defender);
}
