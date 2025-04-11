#ifndef STACK_CONTROLLER_H  
#define STACK_CONTROLLER_H  

#include "models/GameModel.h"  
#include "views/StackView.h"  
#include "CardController.h"  
#include <functional>  

// ���ƶѺ͵��ƶѵ��߼�����
class StackController {
public:
    StackController();

    void init(GameModel* gameModel);

    void initView(StackView* stackView);

    bool handleStackClick();

    // �ӿ��ƶѳ�ȡ���Ƶ����ƶ�
    void drawCardToTray(bool animate = true, const std::function<void()>& callback = nullptr);

    // �滻���ƶѶ�������
    void replaceTrayCard(const CardModel& cardModel, bool animate = true,
        const std::function<void()>& callback = nullptr);

    // ���ÿ��ƶѵ���ص�
    void setOnStackClickCallback(const std::function<bool()>& callback);

    StackView* getView() const;

private:
    GameModel* _gameModel;
    StackView* _stackView;
    std::function<bool()> _onStackClickCallback;
};

#endif // STACK_CONTROLLER_H  