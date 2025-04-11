#ifndef CARD_UTILS_H  
#define CARD_UTILS_H  

#include "models/CardModel.h"  
#include <string>  

class CardUtils {
public:
    // ��ȡ����
    static std::string getFaceName(int face);

    // ��ȡ��ɫ
    static std::string getSuitName(int suit);

    // �ж�ƥ��
    static bool canMatch(const CardModel& card1, const CardModel& card2);

    // ��ȡ��������
    static std::string getCardDescription(const CardModel& card);
};

#endif