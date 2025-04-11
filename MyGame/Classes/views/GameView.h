#ifndef GAME_VIEW_H  
#define GAME_VIEW_H  

#include "cocos2d.h"  
#include "ui/CocosGUI.h"
#include "PlayFieldView.h"  
#include "StackView.h"  
#include <functional>  

// 游戏视图类 负责整个游戏界面的渲染和交互
class GameView : public cocos2d::Scene {
public:
    static GameView* create();

    virtual bool init() override;

    // 获取主牌区视图
    PlayFieldView* getPlayFieldView() const;

    // 获取卡牌堆视图
    StackView* getStackView() const;

    // 设置回退按钮
    void setOnUndoClickCallback(const std::function<void()>& callback);

    // 更新回退按钮
    void updateUndoButton(bool enabled);

    void playMatchAnimation(int cardId, const std::function<void()>& callback = nullptr);

private:
    void createUI();

    PlayFieldView* _playFieldView;
    StackView* _stackView;
    cocos2d::Node* _undoButton;
    std::function<void()> _onUndoClickCallback;
};

#endif