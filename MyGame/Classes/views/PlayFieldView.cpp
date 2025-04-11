#include "PlayFieldView.h"  

USING_NS_CC;

bool PlayFieldView::init() {
    if (!Node::init()) {
        return false;
    }

    // 设置主牌区大小
    this->setContentSize(Size(1080, 1500));

    // 监听卡牌点击事件
    auto listener = EventListenerCustom::create("card_clicked", [this](EventCustom* event) {
        if (event->getUserData()) {
            const CardModel* cardModel = static_cast<const CardModel*>(event->getUserData());
            if (_onCardClickCallback) {
                _onCardClickCallback(cardModel->getId());
            }
        }
        });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

CardView* PlayFieldView::addCard(const CardModel& cardModel) {
    CardView* cardView = CardView::create(cardModel);
    cardView->setPosition(cardModel.getPosition());
    this->addChild(cardView);

    _cardViews[cardModel.getId()] = cardView;

    return cardView;
}

CardView* PlayFieldView::removeCard(int cardId) {
    auto it = _cardViews.find(cardId);
    if (it != _cardViews.end()) {
        CardView* cardView = it->second;
        _cardViews.erase(it);
        cardView->removeFromParent();
        return cardView;
    }

    return nullptr;
}

CardView* PlayFieldView::getCardView(int cardId) const {
    auto it = _cardViews.find(cardId);
    if (it != _cardViews.end()) {
        return it->second;
    }

    return nullptr;
}

void PlayFieldView::setOnCardClickCallback(const std::function<void(int)>& callback) {
    _onCardClickCallback = callback;
}

void PlayFieldView::removeCardById(int cardId) {
    // 查找卡牌视图
    auto it = _cardViews.find(cardId);
    if (it != _cardViews.end()) {
        // 移除
        it->second->removeFromParent();
        _cardViews.erase(it);
    }
}

CardView* PlayFieldView::getCardViewById(int cardId) const {
    auto it = _cardViews.find(cardId);
    if (it != _cardViews.end()) {
        return it->second;
    }
    return nullptr;
}