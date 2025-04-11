#include "PlayFieldController.h"  

PlayFieldController::PlayFieldController() : _gameModel(nullptr), _playFieldView(nullptr) {
}

void PlayFieldController::init(GameModel* gameModel) {
    _gameModel = gameModel;

    const auto& playFieldCards = _gameModel->getPlayfieldCards();
    for (const auto& cardModel : playFieldCards) {
        if (_playFieldView) {
            CardView* cardView = _playFieldView->addCard(cardModel);

            CardController cardController;
            cardController.init(cardModel, cardView);

            _cardControllers[cardModel.getId()] = cardController;
        }
    }
}

void PlayFieldController::initView(PlayFieldView* playFieldView) {
    _playFieldView = playFieldView;

    // 设置卡牌点击回调
    _playFieldView->setOnCardClickCallback([this](int cardId) {
        this->handleCardClick(cardId);
        });

    if (_gameModel) {
        const auto& playFieldCards = _gameModel->getPlayfieldCards();
        for (const auto& cardModel : playFieldCards) {
            CardView* cardView = _playFieldView->addCard(cardModel);

            CardController cardController;
            cardController.init(cardModel, cardView);

            _cardControllers[cardModel.getId()] = cardController;
        }
    }
}

bool PlayFieldController::handleCardClick(int cardId) {
    const CardModel& clickedCard = _gameModel->getPlayfieldCardById(cardId);

    // 判断卡牌是否是行首
    bool isFirstInRow = true;
    float rowY = clickedCard.getPosition().y;
    float clickedX = clickedCard.getPosition().x;

    // 遍历所有卡牌，检查是否有同行且更靠左的卡牌
    for (const auto& card : _gameModel->getPlayfieldCards()) {
        if (std::abs(card.getPosition().y - rowY) < 1.0f &&
            card.getPosition().x < clickedX) {
            isFirstInRow = false;
            break;
        }
    }

    // 如果不是行首卡牌，忽略点击
    if (!isFirstInRow) {
        return false;
    }

    // 是行首卡牌，处理点击事件
    if (_onCardClickCallback) {
        return _onCardClickCallback(cardId);
    }

    return false;
}

void PlayFieldController::setOnCardClickCallback(const std::function<bool(int)>& callback) {
    _onCardClickCallback = callback;
}

PlayFieldView* PlayFieldController::getView() const {
    return _playFieldView;
}

void PlayFieldController::removeCardFromView(int cardId) {  
    if (_playFieldView) {  
        _playFieldView->removeCardById(cardId);  
    }  
}  