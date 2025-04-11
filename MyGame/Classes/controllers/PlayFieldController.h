#ifndef PLAYFIELD_CONTROLLER_H  
#define PLAYFIELD_CONTROLLER_H  

#include "models/GameModel.h"  
#include "views/PlayFieldView.h"  
#include "CardController.h"  
#include <functional>  
#include <map>  

// ��������������
class PlayFieldController {
public:
    PlayFieldController();

    void init(GameModel* gameModel);

    void initView(PlayFieldView* playFieldView);

    bool handleCardClick(int cardId);

    // ���ÿ��Ƶ���ص�
    void setOnCardClickCallback(const std::function<bool(int)>& callback);

    // ��ȡ��������ͼ
    PlayFieldView* getView() const;
    void removeCardFromView(int cardId);
private:
    GameModel* _gameModel;
    PlayFieldView* _playFieldView;
    std::map<int, CardController> _cardControllers;
    std::function<bool(int)> _onCardClickCallback;
};

#endif