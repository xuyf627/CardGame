#include "CardResConfig.h"  

USING_NS_CC;

CardResConfig* CardResConfig::_instance = nullptr;

CardResConfig* CardResConfig::getInstance() {
    if (_instance == nullptr) {
        _instance = new CardResConfig();
    }
    return _instance;
}

CardResConfig::CardResConfig() {
    init();
}

void CardResConfig::init() {
    // 初始化卡牌尺寸
    _cardSize = Size(180, 250);

    // 初始化卡牌背面资源路径
    _cardBackPath = "cards/card_background.png";

    // 初始化花色
    _suitPaths[0] = "suits/club.png";
    _suitPaths[1] = "suits/diamond.png";
    _suitPaths[2] = "suits/heart.png";
    _suitPaths[3] = "suits/spade.png";

    // 初始化红色花色标记 (方块和红桃)
    _isRedSuit = { false, true, true, false };

    // 初始化牌面字符
    _faceChars = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
}

std::string CardResConfig::getCardFacePath(int suit, int face, bool isSmall) const {
    std::string prefix = isSmall ? "small_" : "big_";
    std::string color = _isRedSuit[suit] ? "red_" : "black_";
    std::string faceChar = _faceChars[face];

    return "number/" + prefix + color + faceChar + ".png";
}

std::string CardResConfig::getCardSuitPath(int suit) const {
    return _suitPaths.at(suit);
}

std::string CardResConfig::getCardBackPath() const {
    return _cardBackPath;
}

cocos2d::Size CardResConfig::getCardSize() const {
    return _cardSize;
}