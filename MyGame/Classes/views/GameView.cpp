#include "GameView.h"  
#include "ui/CocosGUI.h"  

USING_NS_CC;
using namespace cocos2d::ui;

GameView* GameView::create() {
    GameView* view = new (std::nothrow) GameView();
    if (view && view->init()) {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool GameView::init() {
    if (!Scene::init()) {
        return false;
    }

    createUI();

    return true;
}

void GameView::createUI() {
    // ������Ϸ����
    auto background = LayerColor::create(Color4B(0, 100, 0, 255));
    this->addChild(background);

    // ������������ͼ
    _playFieldView = PlayFieldView::create();
    _playFieldView->setPosition(Vec2(0, 580));
    this->addChild(_playFieldView);

    // �������ƶ���ͼ
    _stackView = StackView::create();
    _stackView->setPosition(Vec2(0, 0));
    this->addChild(_stackView);

    // ��ť����
    auto buttonBg = LayerColor::create(Color4B(139, 69, 19, 255), 120, 60); // ��ɫ
    buttonBg->setPosition(Vec2(950, 100));

    // ������ɫ��ǩ
    auto textLabel = Label::createWithSystemFont(u8"����", "Arial", 24);
    textLabel->setTextColor(Color4B::WHITE);
    textLabel->setPosition(Vec2(120 / 2, 60 / 2)); // ����  
    buttonBg->addChild(textLabel);

    // ��Ӵ����¼�
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    // ����Ч��
    touchListener->onTouchBegan = [buttonBg](Touch* touch, Event* event) -> bool {
        Vec2 pos = buttonBg->convertToNodeSpace(touch->getLocation());
        Rect rect(0, 0, buttonBg->getContentSize().width, buttonBg->getContentSize().height);

        if (rect.containsPoint(pos)) {
            // ����ʱ�䰵
            buttonBg->setColor(Color3B(100, 50, 10));
            return true;
        }
        return false;
        };

    // �ͷ�Ч��
    touchListener->onTouchEnded = [this, buttonBg](Touch* touch, Event* event) {
        // �ָ�ԭɫ  
        buttonBg->setColor(Color3B(139, 69, 19));

        Vec2 pos = buttonBg->convertToNodeSpace(touch->getLocation());
        Rect rect(0, 0, buttonBg->getContentSize().width, buttonBg->getContentSize().height);

        if (rect.containsPoint(pos)) {
            if (_onUndoClickCallback) {
                _onUndoClickCallback();
            }
        }
        };

    touchListener->onTouchCancelled = [buttonBg](Touch* touch, Event* event) {
        buttonBg->setColor(Color3B(139, 69, 19));
        };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
        touchListener, buttonBg);

    this->addChild(buttonBg);
    _undoButton = buttonBg; // ���水ť��Ϣ

    // ��������
    auto titleLabel = Label::createWithSystemFont(u8"����ƥ����Ϸ", "Arial", 40);
    titleLabel->setPosition(Vec2(540, 100));
    titleLabel->setColor(Color3B::WHITE);
    this->addChild(titleLabel);
}

PlayFieldView* GameView::getPlayFieldView() const {
    return _playFieldView;
}

StackView* GameView::getStackView() const {
    return _stackView;
}

void GameView::setOnUndoClickCallback(const std::function<void()>& callback) {
    _onUndoClickCallback = callback;
}


void GameView::updateUndoButton(bool enabled) {
    auto buttonBg = static_cast<LayerColor*>(_undoButton);

    if (enabled) {
        buttonBg->setColor(Color3B(139, 69, 19));
        buttonBg->setOpacity(255);

        if (!buttonBg->isTouchEnabled()) {
            buttonBg->setTouchEnabled(true);
        }
    }
    else {
        buttonBg->setOpacity(150);

        buttonBg->setTouchEnabled(false);
    }

    auto label = dynamic_cast<Label*>(buttonBg->getChildren().at(0));
    if (label) {
        label->setTextColor(enabled ? Color4B::WHITE : Color4B(200, 200, 200, 150));
    }
}

void GameView::playMatchAnimation(int cardId, const std::function<void()>& callback) {
    CardView* cardView = _playFieldView->getCardView(cardId);
    if (!cardView) {
        if (callback) {
            callback();
        }
        return;
    }

    auto scaleBig = ScaleTo::create(0.1f, 1.2f);
    auto scaleNormal = ScaleTo::create(0.1f, 1.0f);

    if (callback) {
        cardView->runAction(Sequence::create(scaleBig, scaleNormal, CallFunc::create(callback), nullptr));
    }
    else {
        cardView->runAction(Sequence::create(scaleBig, scaleNormal, nullptr));
    }
}