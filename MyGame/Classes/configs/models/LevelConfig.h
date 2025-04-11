#ifndef LEVEL_CONFIG_H  
#define LEVEL_CONFIG_H  

#include <vector>  
#include "cocos2d.h"  

// 卡牌配置结构体
struct CardConfig {
    int cardFace;  // 牌面值  
    int cardSuit;  // 花色  
    cocos2d::Vec2 position;  // 位置  

    CardConfig() : cardFace(0), cardSuit(0), position(0, 0) {}
    CardConfig(int face, int suit, cocos2d::Vec2 pos) : cardFace(face), cardSuit(suit), position(pos) {}
};

// 卡牌布局和初始状态
class LevelConfig {
public:
    void setPlayfield(const std::vector<CardConfig>& playfield);

    void setStack(const std::vector<CardConfig>& stack);

    const std::vector<CardConfig>& getPlayfield() const;

    const std::vector<CardConfig>& getStack() const;

private:
    std::vector<CardConfig> _playfield;  // 主牌区卡牌配置  
    std::vector<CardConfig> _stack;      // 卡牌堆配置  
};

#endif