#include "GameController.h"  
#include "configs/loaders/LevelConfigLoader.h"  
#include "services/GameModelFromLevelGenerator.h"  
#include "services/UndoService.h"  
#include "models/UndoModel.h"  
#include "ui/CocosGUI.h"  

USING_NS_CC;
GameController::GameController()
    : _gameView(nullptr),
    _gameModel(new GameModel()),
    _playFieldController(new PlayFieldController()),
    _stackController(new StackController()),
    _undoManager(new UndoManager()) {
}

GameController::~GameController() {
}

void GameController::startGame(int levelId) {
    LevelConfig levelConfig = LevelConfigLoader::loadLevelConfig(levelId);

    initGame(levelConfig);
}

void GameController::initGame(const LevelConfig& levelConfig) {
    _gameModel = GameModelFromLevelGenerator::generateGameModel(levelConfig);

    _gameView = GameView::create();
    Director::getInstance()->replaceScene(_gameView);

    // ��ʼ��������
    _playFieldController->init(_gameModel.get());
    _playFieldController->initView(_gameView->getPlayFieldView());
    _playFieldController->setOnCardClickCallback([this](int cardId) {
        return this->handleCardClick(cardId);
        });

    _stackController->init(_gameModel.get());
    _stackController->initView(_gameView->getStackView());
    _stackController->setOnStackClickCallback([this]() {
        return this->handleStackClick();
        });

    _undoManager->init();

    // ���û��˰�ť�ص�
    _gameView->setOnUndoClickCallback([this]() {
        this->handleUndo();
        });

    // ���»��˰�ť״̬
    updateUndoButtonState();
}

bool GameController::handleCardClick(int cardId) {
    // ��ȡ����Ŀ��ƺ͵��ƶѶ�������
    const CardModel& playfieldCard = _gameModel->getPlayfieldCardById(cardId);
    const CardModel& topTrayCard = _gameModel->getTopTrayCard();

    // ��鿨���Ƿ�ƥ��
    if (playfieldCard.matches(topTrayCard)) {
        // ƥ��ɹ����滻���ƶѶ�������
        replaceTrayWithPlayFieldCard(cardId);
        return true;
    }

    return false;
}

bool GameController::handleStackClick() {
    // ��鿨�ƶ��Ƿ��п���
    if (_gameModel->hasStackCards()) {
        // �ӿ��ƶѳ�һ�����滻���ƶѶ�������
        replaceTrayWithStackCard();
        return true;
    }

    return false;
}


void GameController::replaceTrayWithPlayFieldCard(int cardId) {
    // ��ȡ����ǰ��״̬
    const CardModel& sourceCard = _gameModel->getPlayfieldCardById(cardId);
    const CardModel& destCard = _gameModel->getTopTrayCard();

    // ��¼��������
    OperationRecord record(OperationType::MATCH_PLAYFIELD, sourceCard, destCard,
        sourceCard.getPosition(), destCard.getPosition());
    _undoManager->recordOperation(record);

    // ����ƥ�䶯��
    _gameView->playMatchAnimation(cardId, [this, cardId]() {
        // �Ƴ�����������
        CardModel cardModel = _gameModel->removePlayfieldCard(cardId);
        // �Ƴ�������ͼ
        _playFieldController->removeCardFromView(cardId);
        // �滻���ƶѶ�������
        _stackController->replaceTrayCard(cardModel, true, [this]() {
            // ���»��˰�ť״̬  
            this->updateUndoButtonState();

            // �����Ϸ�Ƿ����  
            if (_gameModel->isGameOver()) {
                showGameWinUI();
            }
            });
        });
}

void GameController::showGameWinUI() {
    // ��Ӻ�ɫ����
    auto winBg = LayerColor::create(Color4B(0, 0, 0, 150));
    winBg->setContentSize(Director::getInstance()->getVisibleSize());
    _gameView->addChild(winBg, 90);

    auto winLabel = Label::createWithSystemFont(u8"��Ϸʤ����", "Arial", 80);
    winLabel->setPosition(Vec2(540, 1040));
    winLabel->setColor(Color3B(255, 215, 0));
    _gameView->addChild(winLabel, 100);

    auto exitButton = LayerColor::create(Color4B(139, 69, 19, 255), 300, 100);
    exitButton->setPosition(Vec2(390, 850));
    _gameView->addChild(exitButton, 100);

    auto buttonText = Label::createWithSystemFont(u8"�˳���Ϸ", "Arial", 40);
    buttonText->setPosition(Vec2(150, 50));
    buttonText->setColor(Color3B::WHITE);
    exitButton->addChild(buttonText);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    touchListener->onTouchBegan = [exitButton](Touch* touch, Event* event) -> bool {
        Vec2 pos = exitButton->convertToNodeSpace(touch->getLocation());
        Rect rect(0, 0, exitButton->getContentSize().width, exitButton->getContentSize().height);

        if (rect.containsPoint(pos)) {
            exitButton->setColor(Color3B(100, 50, 10));
            return true;
        }
        return false;
        };

    touchListener->onTouchEnded = [this, exitButton](Touch* touch, Event* event) {
        exitButton->setColor(Color3B(139, 69, 19));

        Vec2 pos = exitButton->convertToNodeSpace(touch->getLocation());
        Rect rect(0, 0, exitButton->getContentSize().width, exitButton->getContentSize().height);

        if (rect.containsPoint(pos)) {
            exitGame();
        }
        };


    touchListener->onTouchCancelled = [exitButton](Touch* touch, Event* event) {
        exitButton->setColor(Color3B(139, 69, 19));
        };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
        touchListener, exitButton);

    // ����ʱ
    auto countdownLabel = Label::createWithSystemFont(u8"10����Զ��˳�", "Arial", 30);
    countdownLabel->setPosition(Vec2(540, 750));
    countdownLabel->setColor(Color3B(220, 220, 220));
    _gameView->addChild(countdownLabel, 100);

    int remainTime = 10;
    countdownLabel->schedule([this, countdownLabel, remainTime](float dt) mutable {
        remainTime--;
        if (remainTime <= 0) {
            countdownLabel->unscheduleAllCallbacks();
            exitGame();
        }
        else {
            // ���µ���ʱ�ı�
            std::string text = StringUtils::format(u8"%d����Զ��˳�", remainTime);
            countdownLabel->setString(text);
        }
        }, 1.0f, "countdown");
}

void GameController::exitGame() {
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
    exit(0);
#endif  
}

void GameController::replaceTrayWithStackCard() {
    // ��ȡ����ǰ��״̬
    const CardModel& destCard = _gameModel->getTopTrayCard();

    // ��¼��������
    OperationRecord record(OperationType::DRAW_STACK, CardModel(), destCard,
        cocos2d::Vec2::ZERO, destCard.getPosition());
    _undoManager->recordOperation(record);

    // �ӿ��ƶѳ�һ�����滻���ƶѶ�������
    _stackController->drawCardToTray(true, [this]() {
        // ���»��˰�ť״̬
        this->updateUndoButtonState();
        });
}

void GameController::handleUndo() {
    if (!_undoManager->canUndo()) {
        return;
    }

    // ��ȡ��һ�β�����¼
    OperationRecord record = _undoManager->undoLastOperation();

    // ���ݲ�������ִ�л��˲���
    switch (record.type) {
    case OperationType::MATCH_PLAYFIELD:
        // ����������ƥ�����
        UndoService::undoMatchPlayfield(record, _gameModel.get(), _playFieldController.get(), _stackController.get());
        break;

    case OperationType::DRAW_STACK:
        // ���˳��Ʋ���
        UndoService::undoDrawStack(record, _gameModel.get(), _stackController.get());
        break;

    default:
        break;
    }

    updateUndoButtonState();
}

void GameController::updateUndoButtonState() {
    if (_gameView) {
        _gameView->updateUndoButton(_undoManager->canUndo());
    }
}