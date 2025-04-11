#ifndef CARD_VIEW_H  
#define CARD_VIEW_H  

#include "cocos2d.h"  
#include "models/CardModel.h"  

// ø®≈∆ ”Õº¿‡
class CardView : public cocos2d::Node {
public:
    static CardView* create(const CardModel& cardModel);

    virtual bool init(const CardModel& cardModel);

    int getCardId() const;

    void moveTo(const cocos2d::Vec2& position, float duration = 0.3f,
        const std::function<void()>& callback = nullptr);

    void flip(bool faceUp, float duration = 0.3f,
    const std::function<void()>& callback = nullptr);
private:
    void createCardSprite();

    CardModel _cardModel;
    cocos2d::Sprite* _cardFaceSprite;
    cocos2d::Sprite* _cardBackSprite;
    cocos2d::Sprite* _suitSprite;
    cocos2d::Node* _faceSprite;
    bool _isFaceUp;

};

#endif