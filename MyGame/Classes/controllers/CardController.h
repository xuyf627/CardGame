#ifndef CARD_CONTROLLER_H  
#define CARD_CONTROLLER_H  

#include "models/CardModel.h"  
#include "views/CardView.h"  

// ¿¨ÅÆ¿ØÖÆÆ÷Àà
class CardController {
public:
    CardController();

    void init(const CardModel& cardModel, CardView* cardView);

    const CardModel& getCardModel() const;

    CardView* getCardView() const;

private:
    CardModel _cardModel;
    CardView* _cardView;
};

#endif