#include "CardUtils.h"  

std::string CardUtils::getFaceName(int face) {
    static const std::string faceNames[] = {
        "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
    };

    if (face >= 0 && face < 13) {
        return faceNames[face];
    }

    return "Unknown";
}

std::string CardUtils::getSuitName(int suit) {
    static const std::string suitNames[] = {
        "Ã·»¨", "·½¿é", "ºìÌÒ", "ºÚÌÒ"
    };

    if (suit >= 0 && suit < 4) {
        return suitNames[suit];
    }

    return "Unknown";
}

bool CardUtils::canMatch(const CardModel& card1, const CardModel& card2) {
    int faceDiff = std::abs(card1.getFace() - card2.getFace());
    return faceDiff == 1;
}

std::string CardUtils::getCardDescription(const CardModel& card) {
    return getSuitName(card.getSuit()) + " " + getFaceName(card.getFace());
}