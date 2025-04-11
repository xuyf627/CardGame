#include "StackView.h"  

USING_NS_CC;

bool StackView::init() {
    if (!Node::init()) {
        return false;
    }

    // 设置卡牌堆区域大小
    this->setContentSize(Size(1080, 580));

    // 设置卡牌堆和底牌堆位置
    _stackPosition = Vec2(300, 290);
    _trayPosition = Vec2(780, 290);

    _stackPlaceholder = Sprite::create("cards/card_placeholder.png");
    if (_stackPlaceholder == nullptr) {
        _stackPlaceholder = Sprite::create();
        _stackPlaceholder->setTextureRect(Rect(0, 0, 180, 250));
        _stackPlaceholder->setColor(Color3B(50, 50, 50));
    }
    _stackPlaceholder->setPosition(_stackPosition);
    this->addChild(_stackPlaceholder);

    _trayPlaceholder = Sprite::create("cards/card_placeholder.png");
    if (_trayPlaceholder == nullptr) {
        _trayPlaceholder = Sprite::create();
        _trayPlaceholder->setTextureRect(Rect(0, 0, 180, 250));
        _trayPlaceholder->setColor(Color3B(50, 50, 50));
    }
    _trayPlaceholder->setPosition(_trayPosition);
    this->addChild(_trayPlaceholder);

    // 设置点击事件
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [this](Touch* touch, Event* event) -> bool {
        Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());

        // 检查是否点击了底牌堆
        /*Rect trayRect = Rect(_trayPosition.x - 90, _trayPosition.y - 125, 180, 250);
        if (trayRect.containsPoint(locationInNode)) {
            if (_onTrayClickCallback) {
                _onTrayClickCallback();
            }
            return true;
        }*/

        // 检查是否点击了卡牌堆
        Rect stackRect = Rect(_stackPosition.x - 90, _stackPosition.y - 125, 180, 250);
        if (stackRect.containsPoint(locationInNode)) {
            if (_onStackClickCallback) {
                _onStackClickCallback();
            }
            return true;
        }

        return false;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void StackView::addStackCard(const CardModel& cardModel) {
    CardView* cardView = CardView::create(cardModel);
    cardView->setPosition(_stackPosition);
    cardView->flip(false);
    this->addChild(cardView);

    _stackCards.push_back(cardView);
}

CardView* StackView::popStackCard() {
    if (_stackCards.empty()) {
        return nullptr;
    }

    CardView* cardView = _stackCards.back();
    _stackCards.pop_back();

    return cardView;
}

void StackView::pushTrayCard(const CardModel& cardModel, bool animate, const std::function<void()>& callback) {
    CardView* cardView = CardView::create(cardModel);
    this->addChild(cardView);

    if (animate) {
        cardView->setPosition(cardModel.getPosition());
        cardView->moveTo(_trayPosition, 0.3f, callback);
    }
    else {
        cardView->setPosition(_trayPosition);
        if (callback) {
            callback();
        }
    }

    _trayCards.push_back(cardView);
}

CardView* StackView::popTrayCard() {
    if (_trayCards.empty()) {
        return nullptr;
    }

    CardView* cardView = _trayCards.back();
    _trayCards.pop_back();

    return cardView;
}

CardView* StackView::getTopTrayCardView() const {
    if (_trayCards.empty()) {
        return nullptr;
    }

    return _trayCards.back();
}

void StackView::setOnTrayClickCallback(const std::function<void()>& callback) {
    _onTrayClickCallback = callback;
}

void StackView::setOnStackClickCallback(const std::function<void()>& callback) {
    _onStackClickCallback = callback;
}