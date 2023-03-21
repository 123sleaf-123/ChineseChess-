#include "global.h"
#include "tools.h"

char *c2tUser(struct ChessBoard* board, int code) {
    if (code == PLAYER_1) return "玩家一";
    if (code == PLAYER_2) return "玩家二";
    return "";
}

/**
 * @brief 输入棋子，输出棋子中文名字，区分玩家
 * 
 * @param chess 玩家棋子
 * @return char* 棋子中文名字
 */
char *chessName(struct Chess* chess) {
    // switch(chess->owner) {
    //     // 玩家一是红色
    //     case PLAYER_1: {
    //         switch(chess->type) {
    //             case GENERAL: return "帥";
    //             case CHARIOT: return "俥";
    //             case HORSE: return "傌";
    //             case ARTILLERY: return "炮";
    //             case ELEPHANT: return "相";
    //             case WARRIOR: return "仕";
    //             case SOLDIER: return "兵";
    //         }
    //         break;
    //     }

    //     // 玩家二是绿色
    //     case PLAYER_2: {
    //         switch(chess->type) {
    //             case GENERAL: return "将";
    //             case CHARIOT: return "車";
    //             case HORSE: return "馬";
    //             case ARTILLERY: return "砲";
    //             case ELEPHANT: return "象";
    //             case WARRIOR: return "士";
    //             case SOLDIER: return "卒";
    //         }
    //         break;
    //     }
    // }

    // 整活
    switch(chess->owner) {
        // 玩家一是红色
        case PLAYER_1: {
            switch(chess->type) {
                case GENERAL: return "蚌";
                case CHARIOT: return "创";
                case HORSE: return "孝";
                case ARTILLERY: return "急";
                case ELEPHANT: return "典";
                case WARRIOR: return "绝";
                case SOLDIER: return "对";
            }
            break;
        }

        // 玩家二是绿色
        case PLAYER_2: {
            switch(chess->type) {
                case GENERAL: return "赢";
                case CHARIOT: return "盒";
                case HORSE: return "批";
                case ARTILLERY: return "麻";
                case ELEPHANT: return "寄";
                case WARRIOR: return "乐";
                case SOLDIER: return "退";
            }
            break;
        }
    }

    return "锟";
}