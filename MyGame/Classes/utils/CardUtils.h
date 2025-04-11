#ifndef CARD_UTILS_H  
#define CARD_UTILS_H  

#include "models/CardModel.h"  
#include <string>  

class CardUtils {
public:
    // 获取点数
    static std::string getFaceName(int face);

    // 获取花色
    static std::string getSuitName(int suit);

    // 判断匹配
    static bool canMatch(const CardModel& card1, const CardModel& card2);

    // 获取完整描述
    static std::string getCardDescription(const CardModel& card);
};

#endif