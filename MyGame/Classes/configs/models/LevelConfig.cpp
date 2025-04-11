#include "LevelConfig.h"  


void LevelConfig::setPlayfield(const std::vector<CardConfig>& playfield) {
    _playfield = playfield;
}

void LevelConfig::setStack(const std::vector<CardConfig>& stack) {
    _stack = stack;
}

const std::vector<CardConfig>& LevelConfig::getPlayfield() const {
    return _playfield;
}

const std::vector<CardConfig>& LevelConfig::getStack() const {
    return _stack;
}