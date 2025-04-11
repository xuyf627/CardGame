#ifndef CARD_RES_CONFIG_H  
#define CARD_RES_CONFIG_H  

#include <string>  
#include <map>  
#include <vector>  
#include "cocos2d.h"  

// ���Ƶ���Դ·���ͳߴ���Ϣ
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

    // ��ɫ·��ӳ��
    std::map<int, std::string> _suitPaths;

    // �Ƿ��Ǻ�ɫ��ɫ
    std::vector<bool> _isRedSuit;

    // �����ַ�ӳ��
    std::vector<std::string> _faceChars;
};

#endif