#include "GameModelFromLevelGenerator.h"  

int GameModelFromLevelGenerator::s_nextCardId = 1;

std::unique_ptr<GameModel> GameModelFromLevelGenerator::generateGameModel(const LevelConfig& levelConfig) {
    auto gameModel = std::make_unique<GameModel>();

    // ʹ�ùؿ�����
    const auto& playfieldCards = levelConfig.getPlayfield();
    const auto& stackCards = levelConfig.getStack();

    // Ϊ���򴴽���������
    if (playfieldCards.empty() && stackCards.empty()) {
        CCLOG("No level data found, generating test data");

        // ����16�Ų��Կ��Ʒ���������
        for (int i = 0; i < 16; i++) {
            // ����λ��
            int row = i / 4;
            int col = i % 4;

            // ��ɫ����
            int suit = i % 4;
            int face = i / 4;

            // λ��
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

    // ���õ��ƶѳ�ʼ����
    if (gameModel->getTrayCards().empty() && gameModel->hasStackCards()) {
        CardModel cardModel = gameModel->popStackCard();
        gameModel->pushTrayCard(cardModel);
    }

    return gameModel;
}

int GameModelFromLevelGenerator::generateCardId() {
    return s_nextCardId++;
}



