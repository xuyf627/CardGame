#ifndef GAME_MODEL_H  
#define GAME_MODEL_H  

#include <vector>  
#include "CardModel.h"  

// 游戏数据模型:存储游戏状态和卡牌数据
class GameModel {
public:
    GameModel();

    // 添加卡牌到主牌区
    void addPlayfieldCard(const CardModel& card);

    // 添加卡牌到卡牌堆
    void addStackCard(const CardModel& card);

    // 移除主牌区的卡牌
    CardModel removePlayfieldCard(int cardId);

    // 移除卡牌堆的顶部卡牌
    CardModel popStackCard();

    // 移动卡牌到底牌堆顶部
    void pushTrayCard(const CardModel& card);

    // 移除底牌堆顶部卡牌
    CardModel popTrayCard();

    // 获取主牌区所有卡牌
    const std::vector<CardModel>& getPlayfieldCards() const;

    // 获取卡牌堆所有卡牌
    const std::vector<CardModel>& getStackCards() const;

    // 获取底牌堆所有卡牌
    const std::vector<CardModel>& getTrayCards() const;

    // 获取底牌堆顶部卡牌
    const CardModel& getTopTrayCard() const;

    const CardModel& getPlayfieldCardById(int cardId) const;

    // 判断主牌区是否还有卡牌
    bool hasPlayfieldCards() const;

    // 判断卡牌堆是否还有卡牌
    bool hasStackCards() const;

    bool isGameOver() const;

private:
    std::vector<CardModel> _playfieldCards;  // 主牌堆
    std::vector<CardModel> _stackCards;      // 卡牌堆
    std::vector<CardModel> _trayCards;       // 底牌堆
};

#endif