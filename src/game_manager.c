#include "game_manager.h"
#include "chess_board.h"
#include "operations.h"

GameManager *createGameManager() {
    GameManager *manager = (GameManager *)malloc(sizeof(GameManager));
    if (manager == NULL) {
        fprintf(stderr, "Failed to allocate memory for GameManager\n");
        return NULL;
    }
    manager->board = createChessBoard(); // 创建棋盘
    if (manager->board == NULL) {
        free(manager);
        return NULL;
    }
    manager->command_history = NULL; // 初始化操作记录链表头指针
    return manager;
}

struct ChessBoard *getGameManagerChessBoard(GameManager *manager) {
    return manager->board; // 返回棋盘指针
}

void setGameManagerChessBoard(GameManager *manager, struct ChessBoard *board) {
    manager->board = board; // 设置棋盘指针
}

Command *getGameManagerCommandHistory(GameManager *manager) {
    return manager->command_history; // 返回操作记录链表头指针
}

void setGameManagerCommandHistory(GameManager *manager, Command *command_history) {
    manager->command_history = command_history; // 设置操作记录链表头指针
}

// 添加操作记录到链表中
void addCommandToHistory(GameManager *manager, Command *command) {
    if (manager->command_history == NULL) {
        manager->command_history = command; // 如果链表为空，直接设置为新命令
    } else {
        command->next = manager->command_history;
        manager->command_history = command; // 更新链表头指针
    }
}

// 从链表中删除最后的操作记录（撤回）
void removeLastCommandFromHistory(GameManager *manager) {
    if (manager->command_history == NULL) {
        return; // 链表为空，无法删除
    }
    Command *temp = manager->command_history;
    manager->command_history = manager->command_history->next; // 更新链表头指针
    free(temp); // 释放内存
}

/* ======================================== 覆写operations.h ==========================================*/
int gameManagerSelectChess(GameManager *manager, int src_row, int src_col) {
    return choose(manager->board, src_row, src_col); // 选择棋子
}

int gameManageRmoveChess(GameManager *manager, int src_row, int src_col, int dest_row, int dest_col) {
    return moveChess(manager->board, src_row, src_col, dest_row, dest_col); // 移动棋子
}

bool gameManagerWithdrawCommand(struct ChessBoard *board) {
    return withdraw(board); // 撤回操作
}

int gameManagerFight(GameManager *manager, ChessPtr attacker, ChessPtr defender) {
    struct ChessBoard *board = manager->board;
    
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
        // 将棋子从棋盘上移除
        removeChessfromBoard(board, defender);

        // 将死亡棋子放入死亡栈
        pushDeadChess2Stack(board, defender);
    }
    return true;
}

int gameManagerFightByPos(GameManager *manager, int src_row, int src_col, int dest_row, int dest_col) {
    return fightByPos(manager->board, src_row, src_col, dest_row, dest_col); // 进行战斗
}
