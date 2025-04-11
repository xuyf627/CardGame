#include "GameModelFromLevelGenerator.h"  

int GameModelFromLevelGenerator::s_nextCardId = 1;

std::unique_ptr<GameModel> GameModelFromLevelGenerator::generateGameModel(const LevelConfig& levelConfig) {
    auto gameModel = std::make_unique<GameModel>();

    // 使用关卡配置
    const auto& playfieldCards = levelConfig.getPlayfield();
    const auto& stackCards = levelConfig.getStack();

    // 为空则创建测试数据
    if (playfieldCards.empty() && stackCards.empty()) {
        CCLOG("No level data found, generating test data");

        // 生成16张测试卡牌放在主牌区
        for (int i = 0; i < 16; i++) {
            // 行列位置
            int row = i / 4;
            int col = i % 4;

            // 花色点数
            int suit = i % 4;
            int face = i / 4;

            // 位置
            float x = 200 + col * 230;
            float y = 1400 - row * 280;

            CardModel cardModel(generateCardId(), face, suit, cocos2d::Vec2(x, y));
            gameModel->addPlayfieldCard(cardModel);
        }

        for (int i = 0; i < 12; i++) {
            int suit = (i % 4);
            int face = 4 + (i / 4);

            CardModel cardModel(generateCardId(), face, suit, cocos2d::Vec2::ZERO);
            gameModel->addStackCard(cardModel);
        }
    }
    else {
        for (const auto& cardConfig : playfieldCards) {
            CardModel cardModel(generateCardId(), cardConfig.cardFace, cardConfig.cardSuit, cardConfig.position);
            gameModel->addPlayfieldCard(cardModel);
        }

        for (const auto& cardConfig : stackCards) {
            CardModel cardModel(generateCardId(), cardConfig.cardFace, cardConfig.cardSuit, cocos2d::Vec2::ZERO);
            gameModel->addStackCard(cardModel);
        }
    }

    // 设置底牌堆初始卡牌
    if (gameModel->getTrayCards().empty() && gameModel->hasStackCards()) {
        CardModel cardModel = gameModel->popStackCard();
        gameModel->pushTrayCard(cardModel);
    }

    return gameModel;
}

int GameModelFromLevelGenerator::generateCardId() {
    return s_nextCardId++;
}



