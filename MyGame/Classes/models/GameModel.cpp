#include "GameModel.h"  
#include <algorithm>  

GameModel::GameModel() {
}

void GameModel::addPlayfieldCard(const CardModel& card) {
    _playfieldCards.push_back(card);
}

void GameModel::addStackCard(const CardModel& card) {
    _stackCards.push_back(card);
}

CardModel GameModel::removePlayfieldCard(int cardId) {
    auto it = std::find_if(_playfieldCards.begin(), _playfieldCards.end(),
        [cardId](const CardModel& card) { return card.getId() == cardId; });

    if (it != _playfieldCards.end()) {
        CardModel card = *it;
        _playfieldCards.erase(it);
        return card;
    }

    return CardModel();
}

CardModel GameModel::popStackCard() {
    if (_stackCards.empty()) {
        return CardModel();
    }

    CardModel card = _stackCards.back();
    _stackCards.pop_back();
    return card;
}

void GameModel::pushTrayCard(const CardModel& card) {
    _trayCards.push_back(card);
}

CardModel GameModel::popTrayCard() {
    if (_trayCards.empty()) {
        return CardModel();
    }

    CardModel card = _trayCards.back();
    _trayCards.pop_back();
    return card;
}

const std::vector<CardModel>& GameModel::getPlayfieldCards() const {
    return _playfieldCards;
}

const std::vector<CardModel>& GameModel::getStackCards() const {
    return _stackCards;
}

const std::vector<CardModel>& GameModel::getTrayCards() const {
    return _trayCards;
}

const CardModel& GameModel::getTopTrayCard() const {
    if (_trayCards.empty()) {
        static CardModel emptyCard;
        return emptyCard;
    }

    return _trayCards.back();
}

const CardModel& GameModel::getPlayfieldCardById(int cardId) const {
    auto it = std::find_if(_playfieldCards.begin(), _playfieldCards.end(),
        [cardId](const CardModel& card) { return card.getId() == cardId; });

    if (it != _playfieldCards.end()) {
        return *it;
    }

    static CardModel emptyCard;
    return emptyCard;
}

bool GameModel::hasPlayfieldCards() const {
    return !_playfieldCards.empty();
}

bool GameModel::hasStackCards() const {
    return !_stackCards.empty();
}

bool GameModel::isGameOver() const {
    return _playfieldCards.empty();
}