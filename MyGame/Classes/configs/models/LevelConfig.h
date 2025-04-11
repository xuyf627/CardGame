#ifndef LEVEL_CONFIG_H  
#define LEVEL_CONFIG_H  

#include <vector>  
#include "cocos2d.h"  

// �������ýṹ��
struct CardConfig {
    int cardFace;  // ����ֵ  
    int cardSuit;  // ��ɫ  
    cocos2d::Vec2 position;  // λ��  

    CardConfig() : cardFace(0), cardSuit(0), position(0, 0) {}
    CardConfig(int face, int suit, cocos2d::Vec2 pos) : cardFace(face), cardSuit(suit), position(pos) {}
};

// ���Ʋ��ֺͳ�ʼ״̬
class LevelConfig {
public:
    void setPlayfield(const std::vector<CardConfig>& playfield);

    void setStack(const std::vector<CardConfig>& stack);

    const std::vector<CardConfig>& getPlayfield() const;

    const std::vector<CardConfig>& getStack() const;

private:
    std::vector<CardConfig> _playfield;  // ��������������  
    std::vector<CardConfig> _stack;      // ���ƶ�����  
};

#endif