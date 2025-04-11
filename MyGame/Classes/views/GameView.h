#ifndef GAME_VIEW_H  
#define GAME_VIEW_H  

#include "cocos2d.h"  
#include "ui/CocosGUI.h"
#include "PlayFieldView.h"  
#include "StackView.h"  
#include <functional>  

// ��Ϸ��ͼ�� ����������Ϸ�������Ⱦ�ͽ���
class GameView : public cocos2d::Scene {
public:
    static GameView* create();

    virtual bool init() override;

    // ��ȡ��������ͼ
    PlayFieldView* getPlayFieldView() const;

    // ��ȡ���ƶ���ͼ
    StackView* getStackView() const;

    // ���û��˰�ť
    void setOnUndoClickCallback(const std::function<void()>& callback);

    // ���»��˰�ť
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