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

    // 初始化控制器
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

    // 设置回退按钮回调
    _gameView->setOnUndoClickCallback([this]() {
        this->handleUndo();
        });

    // 更新回退按钮状态
    updateUndoButtonState();
}

bool GameController::handleCardClick(int cardId) {
    // 获取点击的卡牌和底牌堆顶部卡牌
    const CardModel& playfieldCard = _gameModel->getPlayfieldCardById(cardId);
    const CardModel& topTrayCard = _gameModel->getTopTrayCard();

    // 检查卡牌是否匹配
    if (playfieldCard.matches(topTrayCard)) {
        // 匹配成功，替换底牌堆顶部卡牌
        replaceTrayWithPlayFieldCard(cardId);
        return true;
    }

    return false;
}

bool GameController::handleStackClick() {
    // 检查卡牌堆是否还有卡牌
    if (_gameModel->hasStackCards()) {
        // 从卡牌堆抽一张牌替换底牌堆顶部卡牌
        replaceTrayWithStackCard();
        return true;
    }

    return false;
}


void GameController::replaceTrayWithPlayFieldCard(int cardId) {
    // 获取操作前的状态
    const CardModel& sourceCard = _gameModel->getPlayfieldCardById(cardId);
    const CardModel& destCard = _gameModel->getTopTrayCard();

    // 记录撤销操作
    OperationRecord record(OperationType::MATCH_PLAYFIELD, sourceCard, destCard,
        sourceCard.getPosition(), destCard.getPosition());
    _undoManager->recordOperation(record);

    // 播放匹配动画
    _gameView->playMatchAnimation(cardId, [this, cardId]() {
        // 移除主牌区卡牌
        CardModel cardModel = _gameModel->removePlayfieldCard(cardId);
        // 移除卡牌视图
        _playFieldController->removeCardFromView(cardId);
        // 替换底牌堆顶部卡牌
        _stackController->replaceTrayCard(cardModel, true, [this]() {
            // 更新回退按钮状态  
            this->updateUndoButtonState();

            // 检查游戏是否结束  
            if (_gameModel->isGameOver()) {
                showGameWinUI();
            }
            });
        });
}

void GameController::showGameWinUI() {
    // 添加黑色覆盖
    auto winBg = LayerColor::create(Color4B(0, 0, 0, 150));
    winBg->setContentSize(Director::getInstance()->getVisibleSize());
    _gameView->addChild(winBg, 90);

    auto winLabel = Label::createWithSystemFont(u8"游戏胜利！", "Arial", 80);
    winLabel->setPosition(Vec2(540, 1040));
    winLabel->setColor(Color3B(255, 215, 0));
    _gameView->addChild(winLabel, 100);

    auto exitButton = LayerColor::create(Color4B(139, 69, 19, 255), 300, 100);
    exitButton->setPosition(Vec2(390, 850));
    _gameView->addChild(exitButton, 100);

    auto buttonText = Label::createWithSystemFont(u8"退出游戏", "Arial", 40);
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

    // 倒计时
    auto countdownLabel = Label::createWithSystemFont(u8"10秒后自动退出", "Arial", 30);
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
            // 更新倒计时文本
            std::string text = StringUtils::format(u8"%d秒后自动退出", remainTime);
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
    // 获取操作前的状态
    const CardModel& destCard = _gameModel->getTopTrayCard();

    // 记录撤销操作
    OperationRecord record(OperationType::DRAW_STACK, CardModel(), destCard,
        cocos2d::Vec2::ZERO, destCard.getPosition());
    _undoManager->recordOperation(record);

    // 从卡牌堆抽一张牌替换底牌堆顶部卡牌
    _stackController->drawCardToTray(true, [this]() {
        // 更新回退按钮状态
        this->updateUndoButtonState();
        });
}

void GameController::handleUndo() {
    if (!_undoManager->canUndo()) {
        return;
    }

    // 获取上一次操作记录
    OperationRecord record = _undoManager->undoLastOperation();

    // 根据操作类型执行回退操作
    switch (record.type) {
    case OperationType::MATCH_PLAYFIELD:
        // 回退主牌区匹配操作
        UndoService::undoMatchPlayfield(record, _gameModel.get(), _playFieldController.get(), _stackController.get());
        break;

    case OperationType::DRAW_STACK:
        // 回退抽牌操作
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