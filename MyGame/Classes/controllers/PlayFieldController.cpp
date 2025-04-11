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

    // ���ÿ��Ƶ���ص�
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

    // �жϿ����Ƿ�������
    bool isFirstInRow = true;
    float rowY = clickedCard.getPosition().y;
    float clickedX = clickedCard.getPosition().x;

    // �������п��ƣ�����Ƿ���ͬ���Ҹ�����Ŀ���
    for (const auto& card : _gameModel->getPlayfieldCards()) {
        if (std::abs(card.getPosition().y - rowY) < 1.0f &&
            card.getPosition().x < clickedX) {
            isFirstInRow = false;
            break;
        }
    }

    // ����������׿��ƣ����Ե��
    if (!isFirstInRow) {
        return false;
    }

    // �����׿��ƣ��������¼�
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