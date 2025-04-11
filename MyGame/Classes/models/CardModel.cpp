#include "CardModel.h"  

USING_NS_CC;

CardModel::CardModel() : _id(-1), _face(0), _suit(0), _position(Vec2::ZERO) {
}

CardModel::CardModel(int id, int face, int suit, const Vec2& position)
    : _id(id), _face(face), _suit(suit), _position(position) {
}

int CardModel::getId() const {
    return _id;
}

int CardModel::getFace() const {
    return _face;
}

int CardModel::getSuit() const {
    return _suit;
}

Vec2 CardModel::getPosition() const {
    return _position;
}

void CardModel::setPosition(const Vec2& position) {
    _position = position;
}

bool CardModel::matches(const CardModel& other) const {
    // ø®≈∆∆•≈‰£∫µ„ ˝œ‡≤Ó1
    int faceDiff = std::abs(_face - other.getFace());
    return faceDiff == 1;
}

