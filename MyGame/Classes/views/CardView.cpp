#include "CardView.h"  
#include "configs/models/CardResConfig.h"  
#include "utils/CardUtils.h"
USING_NS_CC;

CardView* CardView::create(const CardModel& cardModel) {
    CardView* view = new (std::nothrow) CardView();
    if (view && view->init(cardModel)) {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool CardView::init(const CardModel& cardModel) {
    if (!Node::init()) {
        return false;
    }

    _cardModel = cardModel;
    _isFaceUp = true;

    createCardSprite();

    // 触摸事件监听器
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->setSwallowTouches(false);
    listener->onTouchBegan = [this](Touch* touch, Event* event) -> bool {
        //Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
        //Size s = this->getContentSize();
        //Rect rect = Rect(0, 0, s.width, s.height);
        ////Rect rect = _cardFaceSprite->getBoundingBox();
        //if (rect.containsPoint(locationInNode)) {
        //    this->setScale(0.95f);
        //    return true;
        //}
        cocos2d::Vec2 stackPosition = Vec2(300, 290);
        Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
        Rect stackRect = Rect(stackPosition.x - 90, stackPosition.y - 125, 180, 250);
        if (stackRect.containsPoint(locationInNode)) {
            return false;
        }
        locationInNode = this->convertToNodeSpace(touch->getLocation());
        /*Size s = this->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);*/
        Rect rect = _cardFaceSprite->getBoundingBox();
        if (rect.containsPoint(locationInNode)) {
            return true;
        }
        return false;
    };
    
    
    listener->onTouchEnded = [this](Touch* touch, Event* event) {
        this->setScale(1.0f);

        // 触发点击回调
        EventCustom customEvent("card_clicked");
        customEvent.setUserData(&_cardModel);
        _eventDispatcher->dispatchEvent(&customEvent);
        };

    listener->onTouchCancelled = [this](Touch* touch, Event* event) {
        this->setScale(1.0f);
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // 设置初始位置
    this->setPosition(_cardModel.getPosition());

    return true;
}

int CardView::getCardId() const {
    return _cardModel.getId();
}

void CardView::moveTo(const Vec2& position, float duration, const std::function<void()>& callback) {
    auto moveTo = MoveTo::create(duration, position);

    if (callback) {
        auto callFunc = CallFunc::create(callback);
        this->runAction(Sequence::create(moveTo, callFunc, nullptr));
    }
    else {
        this->runAction(moveTo);
    }
}

void CardView::flip(bool faceUp, float duration, const std::function<void()>& callback) {
    if (_isFaceUp == faceUp) {
        if (callback) {
            callback();
        }
        return;
    }

    _isFaceUp = faceUp;

    // 执行翻转
    auto scaleDown = ScaleTo::create(duration / 2, 1.0f, 0.0f);

    auto flipAction = CallFunc::create([this, faceUp]() {
        if (faceUp) {
            // 显示正面
            _cardBackSprite->setVisible(false);
            _cardFaceSprite->setVisible(true);
            if (_suitSprite) {
                _suitSprite->setVisible(true);
            }
            if (_faceSprite) {
                _faceSprite->setVisible(true);
            }
        }
        else {
            // 显示背面
            _cardBackSprite->setVisible(true);
            _cardFaceSprite->setVisible(false);
            if (_suitSprite) {
                _suitSprite->setVisible(false);
            }
            if (_faceSprite) {
                _faceSprite->setVisible(false);
            }
        }
        });

    auto scaleUp = ScaleTo::create(duration / 2, 1.0f, 1.0f);

    // 创建动作序列
    if (callback) {
        auto callbackAction = CallFunc::create(callback);
        this->runAction(Sequence::create(scaleDown, flipAction, scaleUp, callbackAction, nullptr));
    }
    else {
        this->runAction(Sequence::create(scaleDown, flipAction, scaleUp, nullptr));
    }
}
void CardView::createCardSprite() {
    auto cardResConfig = CardResConfig::getInstance();


    // 创建卡牌背景
    _cardFaceSprite = Sprite::create("cards/card_placeholder.png");
    if (_cardFaceSprite == nullptr) {
        _cardFaceSprite = Sprite::create();
        _cardFaceSprite->setTextureRect(Rect(0, 0, 180, 250));
        _cardFaceSprite->setColor(Color3B::WHITE);
    }
    _cardFaceSprite->setPosition(Vec2::ZERO);
    _cardFaceSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
    //this->setAnchorPoint(Vec2(0.5f, 0.5f));
    //// 所有子精灵一致
    //_cardFaceSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
    //_cardBackSprite->setAnchorPoint(Vec2(0.5f, 0.5f));


    this->addChild(_cardFaceSprite);

    // 创建卡牌背面
    _cardBackSprite = Sprite::create(cardResConfig->getCardBackPath());
    if (_cardBackSprite == nullptr) {
        // 创建蓝色矩形
        _cardBackSprite = Sprite::create("cards/card_placeholder.png");
        /*_cardBackSprite->setTextureRect(Rect(0, 0, 180, 250));*/
        _cardBackSprite->setColor(Color3B(50, 50, 200));
    }
    _cardBackSprite->setPosition(Vec2::ZERO);
    _cardBackSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
    _cardBackSprite->setVisible(false);
    this->addChild(_cardBackSprite);

    // 创建花色
    std::string suitPath = cardResConfig->getCardSuitPath(_cardModel.getSuit());
    _suitSprite = Sprite::create(suitPath);
    if (_suitSprite == nullptr) {
        _suitSprite = Sprite::create();
        _suitSprite->setTextureRect(Rect(0, 0, 40, 40));

        switch (_cardModel.getSuit()) {
        case 0: // 梅花
            _suitSprite->setColor(Color3B::BLACK);
            break;
        case 1: // 方块
            _suitSprite->setColor(Color3B::RED);
            break;
        case 2: // 红桃
            _suitSprite->setColor(Color3B(255, 100, 100));
            break;
        case 3: // 黑桃
            _suitSprite->setColor(Color3B(50, 50, 50));
            break;
        }
    }
    _suitSprite->setPosition(Vec2(0, 40));
    _suitSprite->setScale(0.8f);
    this->addChild(_suitSprite);

    // 创建点数
    std::string faceText = CardUtils::getFaceName(_cardModel.getFace());
    auto faceLabel = Label::createWithSystemFont(faceText, "Arial", 36);
    faceLabel->setPosition(Vec2(0, -40));
    faceLabel->setColor((_cardModel.getSuit() == 1 || _cardModel.getSuit() == 2) ? Color3B::RED : Color3B::BLACK);
    this->addChild(faceLabel);

    _faceSprite = faceLabel;

    Size cardSize = cardResConfig->getCardSize();
    this->setContentSize(cardSize);
}

