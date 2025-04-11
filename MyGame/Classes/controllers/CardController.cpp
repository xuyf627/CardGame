#include "CardController.h"  

CardController::CardController() : _cardView(nullptr) {
}

void CardController::init(const CardModel& cardModel, CardView* cardView) {
    _cardModel = cardModel;
    _cardView = cardView;
}

const CardModel& CardController::getCardModel() const {
    return _cardModel;
}

CardView* CardController::getCardView() const {
    return _cardView;
}

