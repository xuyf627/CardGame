#include "StackController.h"  

StackController::StackController() : _gameModel(nullptr), _stackView(nullptr) {
}

void StackController::init(GameModel* gameModel) {
    _gameModel = gameModel;

    if (_gameModel && _stackView) {
        // ³õÊ¼»¯¿¨ÅÆ¶Ñ
        const auto& stackCards = _gameModel->getStackCards();
        for (const auto& cardModel : stackCards) {
            _stackView->addStackCard(cardModel);
        }

        // ³õÊ¼»¯µ×ÅÆ¶Ñ 
        const auto& trayCards = _gameModel->getTrayCards();
        for (const auto& cardModel : trayCards) {
            _stackView->pushTrayCard(cardModel, false);
        }
    }
}

void StackController::initView(StackView* stackView) {
    _stackView = stackView;

    _stackView->setOnStackClickCallback([this]() {
        this->handleStackClick();
        });

    if (_gameModel) {
        // ¿¨ÅÆ¶Ñ
        const auto& stackCards = _gameModel->getStackCards();
        for (const auto& cardModel : stackCards) {
            _stackView->addStackCard(cardModel);
        }

        // µ×ÅÆ¶Ñ
        const auto& trayCards = _gameModel->getTrayCards();
        for (const auto& cardModel : trayCards) {
            _stackView->pushTrayCard(cardModel, false);
        }
    }
}

bool StackController::handleStackClick() {
    if (_onStackClickCallback) {
        return _onStackClickCallback();
    }

    return false;
}

void StackController::drawCardToTray(bool animate, const std::function<void()>& callback) {
    if (!_gameModel || !_stackView) {
        if (callback) {
            callback();
        }
        return;
    }

    // ´Ó¿¨ÅÆ¶ÑÈ¡Ò»ÕÅÅÆ
    if (_gameModel->hasStackCards()) {
        CardModel cardModel = _gameModel->popStackCard();

        CardView* cardView = _stackView->popStackCard();

        if (cardView) {
            cardView->removeFromParent();
        }

        _gameModel->pushTrayCard(cardModel);
        _stackView->pushTrayCard(cardModel, animate, callback);
    }
    else {
        if (callback) {
            callback();
        }
    }
}

void StackController::replaceTrayCard(const CardModel& cardModel, bool animate, const std::function<void()>& callback) {
    if (!_gameModel || !_stackView) {
        if (callback) {
            callback();
        }
        return;
    }

    // Ìí¼ÓÐÂ¿¨ÅÆµ½µ×ÅÆ¶Ñ  
    _gameModel->pushTrayCard(cardModel);
    
    _stackView->pushTrayCard(cardModel, animate, callback);
}

void StackController::setOnStackClickCallback(const std::function<bool()>& callback) {
    _onStackClickCallback = callback;
}

StackView* StackController::getView() const {
    return _stackView;
}