#include "StackController.h"  

StackController::StackController() : _gameModel(nullptr), _stackView(nullptr) {
}

void StackController::init(GameModel* gameModel) {
    _gameModel = gameModel;

    if (_gameModel && _stackView) {
        // ��ʼ�����ƶ�
        const auto& stackCards = _gameModel->getStackCards();
        for (const auto& cardModel : stackCards) {
            _stackView->addStackCard(cardModel);
        }

        // ��ʼ�����ƶ� 
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
        // ���ƶ�
        const auto& stackCards = _gameModel->getStackCards();
        for (const auto& cardModel : stackCards) {
            _stackView->addStackCard(cardModel);
        }

        // ���ƶ�
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

    // �ӿ��ƶ�ȡһ����
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

    // ����¿��Ƶ����ƶ�  
    _gameModel->pushTrayCard(cardModel);
    
    _stackView->pushTrayCard(cardModel, animate, callback);
}

void StackController::setOnStackClickCallback(const std::function<bool()>& callback) {
    _onStackClickCallback = callback;
}

StackView* StackController::getView() const {
    return _stackView;
}