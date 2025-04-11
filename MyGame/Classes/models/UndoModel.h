#ifndef UNDO_MODEL_H  
#define UNDO_MODEL_H  

#include <vector>  
#include "CardModel.h"  

// ��������ö��
enum class OperationType {
    NONE,
    DRAW_STACK,          // ���ƶѳ���
    MATCH_PLAYFIELD,     // ƥ����������
    REPLACE_TRAY         // �滻����
};

// ������¼
struct OperationRecord {
    OperationType type;          // ��������
    CardModel sourceCard;        // Դ����
    CardModel destinationCard;   // Ŀ�꿨��
    cocos2d::Vec2 sourcePosition;      // Դλ��
    cocos2d::Vec2 destinationPosition; // Ŀ��λ��

    OperationRecord() : type(OperationType::NONE) {}

    OperationRecord(OperationType t, const CardModel& src, const CardModel& dest,
        const cocos2d::Vec2& srcPos, const cocos2d::Vec2& destPos)
        : type(t), sourceCard(src), destinationCard(dest),
        sourcePosition(srcPos), destinationPosition(destPos) {
    }
};

// ���˲�������
class UndoModel {
public:
    UndoModel();

    void addRecord(const OperationRecord& record);

    OperationRecord popRecord();

    void clear();

    bool canUndo() const;

private:
    std::vector<OperationRecord> _operations;  // ������¼�б�
};

#endif