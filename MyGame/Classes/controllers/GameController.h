#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "models/GameModel.h"
#include "views/GameView.h"
#include "PlayFieldController.h"
#include "StackController.h"
#include "managers/UndoManager.h"
#include "configs/models/LevelConfig.h"
#include <memory>

// ��Ϸ��������
class GameController {
public:
    GameController();
    ~GameController();

    // levelId �ؿ�ID
    void startGame(int levelId);

    bool handleCardClick(int cardId);

    bool handleStackClick();

    // �滻���ƶѶ�������Ϊ����������
    void replaceTrayWithPlayFieldCard(int cardId);

    // �滻���ƶѶ�������Ϊ���ƶѿ���
    void replaceTrayWithStackCard();

    void handleUndo();
    void exitGame();
    void showGameWinUI();

private:
    void initGame(const LevelConfig& levelConfig);

    // ���»��˰�ť״̬
    void updateUndoButtonState();

    GameView* _gameView;
    std::unique_ptr<GameModel> _gameModel;
    std::unique_ptr<PlayFieldController> _playFieldController;
    std::unique_ptr<StackController> _stackController;
    std::unique_ptr<UndoManager> _undoManager;
};

#endif