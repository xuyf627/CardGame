#ifndef CARD_MODEL_H  
#define CARD_MODEL_H  

#include <string>  
#include "cocos2d.h"  

// ��������ģ��
class CardModel {
public:
    CardModel();
    CardModel(int id, int face, int suit, const cocos2d::Vec2& position);

    int getId() const;

    int getFace() const;

    int getSuit() const;

    cocos2d::Vec2 getPosition() const;

    void setPosition(const cocos2d::Vec2& position);

    bool matches(const CardModel& other) const;

    int getRow() const { return _row; }
    void setRow(int row) { _row = row; }

    int getIndex() const { return _index; }
    void setIndex(int index) { _index = index; }

private:
    int _id;                // ����ΨһID
    int _face;              // ���Ƶ��� 0=A, 1=2...12=K
    int _suit;              // ���ƻ�ɫ 0=÷��, 1=����, 2=����, 3=����
    cocos2d::Vec2 _position; // ����λ��
    int _row;    // ������
    int _index;  // ��������λ��
};

#endif