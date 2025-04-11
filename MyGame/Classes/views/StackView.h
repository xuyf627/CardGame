#ifndef STACK_VIEW_H  
#define STACK_VIEW_H  

#include "cocos2d.h"  
#include "CardView.h"  
#include "models/CardModel.h"  
#include <functional>  

// ���ƶ���ͼ
class StackView : public cocos2d::Node {
public:
    CREATE_FUNC(StackView);

    virtual bool init() override;

    void addStackCard(const CardModel& cardModel);

    CardView* popStackCard();

    // ��ӿ��Ƶ����ƶ�
    void pushTrayCard(const CardModel& cardModel, bool animate = true,
        const std::function<void()>& callback = nullptr);

    // �ӵ��ƶѶ����Ƴ�����
    CardView* popTrayCard();

    // ��ȡ���ƶѶ���������ͼ
    CardView* getTopTrayCardView() const;

    void setOnTrayClickCallback(const std::function<void()>& callback);

    // ���ÿ��ƶѵ���ص�
    void setOnStackClickCallback(const std::function<void()>& callback);

private:
    cocos2d::Vec2 _stackPosition;
    cocos2d::Vec2 _trayPosition;
    std::vector<CardView*> _stackCards;
    std::vector<CardView*> _trayCards;
    std::function<void()> _onTrayClickCallback;
    std::function<void()> _onStackClickCallback;
    cocos2d::Sprite* _stackPlaceholder;
    cocos2d::Sprite* _trayPlaceholder;
};

#endif