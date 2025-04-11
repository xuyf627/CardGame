#ifndef STACK_CONTROLLER_H  
#define STACK_CONTROLLER_H  

#include "models/GameModel.h"  
#include "views/StackView.h"  
#include "CardController.h"  
#include <functional>  

// ¿¨ÅÆ¶ÑºÍµ×ÅÆ¶ÑµÄÂß¼­´¦Àí
class StackController {
public:
    StackController();

    void init(GameModel* gameModel);

    void initView(StackView* stackView);

    bool handleStackClick();

    // ´Ó¿¨ÅÆ¶Ñ³éÈ¡¿¨ÅÆµ½µ×ÅÆ¶Ñ
    void drawCardToTray(bool animate = true, const std::function<void()>& callback = nullptr);

    // Ìæ»»µ×ÅÆ¶Ñ¶¥²¿¿¨ÅÆ
    void replaceTrayCard(const CardModel& cardModel, bool animate = true,
        const std::function<void()>& callback = nullptr);

    // ÉèÖÃ¿¨ÅÆ¶Ñµã»÷»Øµ÷
    void setOnStackClickCallback(const std::function<bool()>& callback);

    StackView* getView() const;

private:
    GameModel* _gameModel;
    StackView* _stackView;
    std::function<bool()> _onStackClickCallback;
};

#endif // STACK_CONTROLLER_H  