#ifndef PLAYFIELD_VIEW_H  
#define PLAYFIELD_VIEW_H  

#include "cocos2d.h"  
#include "CardView.h"  
#include "models/CardModel.h"  
#include <functional>  
#include <map>  

// 主牌区视图
class PlayFieldView : public cocos2d::Node {
public:
    CREATE_FUNC(PlayFieldView);

    virtual bool init() override;

    CardView* addCard(const CardModel& cardModel);

    CardView* removeCard(int cardId);

    CardView* getCardView(int cardId) const;
    
    // 设置卡牌点击回调
    void setOnCardClickCallback(const std::function<void(int)>& callback);
    void removeCardById(int cardId);
    CardView* getCardViewById(int cardId) const;


private:
    std::map<int, CardView*> _cardViews;
    std::function<void(int)> _onCardClickCallback;
};

#endif