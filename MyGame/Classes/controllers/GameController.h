#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "models/GameModel.h"
#include "views/GameView.h"
#include "PlayFieldController.h"
#include "StackController.h"
#include "managers/UndoManager.h"
#include "configs/models/LevelConfig.h"
#include <memory>

// ÓÎÏ·¿ØÖÆÆ÷Àà
class GameController {
public:
    GameController();
    ~GameController();

    // levelId ¹Ø¿¨ID
    void startGame(int levelId);

    bool handleCardClick(int cardId);

    bool handleStackClick();

    // Ìæ»»µ×ÅÆ¶Ñ¶¥²¿¿¨ÅÆÎªÖ÷ÅÆÇø¿¨ÅÆ
    void replaceTrayWithPlayFieldCard(int cardId);

    // Ìæ»»µ×ÅÆ¶Ñ¶¥²¿¿¨ÅÆÎª¿¨ÅÆ¶Ñ¿¨ÅÆ
    void replaceTrayWithStackCard();

    void handleUndo();
    void exitGame();
    void showGameWinUI();

private:
    void initGame(const LevelConfig& levelConfig);

    // ¸üÐÂ»ØÍË°´Å¥×´Ì¬
    void updateUndoButtonState();

    GameView* _gameView;
    std::unique_ptr<GameModel> _gameModel;
    std::unique_ptr<PlayFieldController> _playFieldController;
    std::unique_ptr<StackController> _stackController;
    std::unique_ptr<UndoManager> _undoManager;
};

#endif