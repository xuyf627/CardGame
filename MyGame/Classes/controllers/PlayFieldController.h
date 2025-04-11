#ifndef PLAYFIELD_CONTROLLER_H  
#define PLAYFIELD_CONTROLLER_H  

#include "models/GameModel.h"  
#include "views/PlayFieldView.h"  
#include "CardController.h"  
#include <functional>  
#include <map>  

// 主牌区控制器类
class PlayFieldController {
public:
    PlayFieldController();

    void init(GameModel* gameModel);

    void initView(PlayFieldView* playFieldView);

    bool handleCardClick(int cardId);

    // 设置卡牌点击回调
    void setOnCardClickCallback(const std::function<bool(int)>& callback);

    // 获取主牌区视图
    PlayFieldView* getView() const;
    void removeCardFromView(int cardId);
private:
    GameModel* _gameModel;
    PlayFieldView* _playFieldView;
    std::map<int, CardController> _cardControllers;
    std::function<bool(int)> _onCardClickCallback;
};

#endif