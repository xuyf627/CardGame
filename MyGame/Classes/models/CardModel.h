#ifndef CARD_MODEL_H  
#define CARD_MODEL_H  

#include <string>  
#include "cocos2d.h"  

// 卡牌数据模型
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
    int _id;                // 卡牌唯一ID
    int _face;              // 卡牌点数 0=A, 1=2...12=K
    int _suit;              // 卡牌花色 0=梅花, 1=方块, 2=红桃, 3=黑桃
    cocos2d::Vec2 _position; // 卡牌位置
    int _row;    // 所在行
    int _index;  // 行内索引位置
};

#endif