#ifndef UNDO_MODEL_H  
#define UNDO_MODEL_H  

#include <vector>  
#include "CardModel.h"  

// 操作类型枚举
enum class OperationType {
    NONE,
    DRAW_STACK,          // 从牌堆抽牌
    MATCH_PLAYFIELD,     // 匹配主牌区牌
    REPLACE_TRAY         // 替换底牌
};

// 操作记录
struct OperationRecord {
    OperationType type;          // 操作类型
    CardModel sourceCard;        // 源卡牌
    CardModel destinationCard;   // 目标卡牌
    cocos2d::Vec2 sourcePosition;      // 源位置
    cocos2d::Vec2 destinationPosition; // 目标位置

    OperationRecord() : type(OperationType::NONE) {}

    OperationRecord(OperationType t, const CardModel& src, const CardModel& dest,
        const cocos2d::Vec2& srcPos, const cocos2d::Vec2& destPos)
        : type(t), sourceCard(src), destinationCard(dest),
        sourcePosition(srcPos), destinationPosition(destPos) {
    }
};

// 回退操作数据
class UndoModel {
public:
    UndoModel();

    void addRecord(const OperationRecord& record);

    OperationRecord popRecord();

    void clear();

    bool canUndo() const;

private:
    std::vector<OperationRecord> _operations;  // 操作记录列表
};

#endif