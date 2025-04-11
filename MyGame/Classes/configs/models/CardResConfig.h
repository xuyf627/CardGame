#ifndef CARD_RES_CONFIG_H  
#define CARD_RES_CONFIG_H  

#include <string>  
#include <map>  
#include <vector>  
#include "cocos2d.h"  

// 卡牌的资源路径和尺寸信息
class CardResConfig {
public:
    static CardResConfig* getInstance();

    std::string getCardFacePath(int suit, int face, bool isSmall = false) const;

    std::string getCardSuitPath(int suit) const;

    std::string getCardBackPath() const;

    cocos2d::Size getCardSize() const;

private:
    CardResConfig();
    void init();

    static CardResConfig* _instance;
    std::string _cardBackPath;
    cocos2d::Size _cardSize;

    // 花色路径映射
    std::map<int, std::string> _suitPaths;

    // 是否是红色花色
    std::vector<bool> _isRedSuit;

    // 牌面字符映射
    std::vector<std::string> _faceChars;
};

#endif