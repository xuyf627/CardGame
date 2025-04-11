#include "UndoService.h"  

void UndoService::undoMatchPlayfield(const OperationRecord& record, GameModel* gameModel,
    PlayFieldController* playFieldController, StackController* stackController) {
    if (!gameModel || !playFieldController || !stackController) {
        return;
    }

    // »Ö¸´Ö÷ÅÆÇø¿¨ÅÆ
    CardModel sourceCard = record.sourceCard;
    sourceCard.setPosition(record.sourcePosition);
    gameModel->addPlayfieldCard(sourceCard);

    // »Ö¸´µ×ÅÆ¶Ñ¿¨ÅÆ
    CardModel destCard = record.destinationCard;
    destCard.setPosition(record.destinationPosition);

    // ÒÆ³ıµ±Ç°µ×ÅÆ¶Ñ¶¥²¿¿¨ÅÆ
    gameModel->popTrayCard();

    // ÖØĞÂÌí¼ÓÔ­µ×ÅÆ¶Ñ¶¥²¿¿¨ÅÆ
    gameModel->pushTrayCard(destCard);

    // ¸üĞÂÊÓÍ¼
    PlayFieldView* playFieldView = playFieldController->getView();
    StackView* stackView = stackController->getView();

    if (playFieldView && stackView) {
        // Ìí¼ÓÖ÷ÅÆÇø¿¨ÅÆÊÓÍ¼
        playFieldView->addCard(sourceCard);

        // ÒÆ³ı²¢Ìæ»»µ×ÅÆ¶Ñ¶¥²¿¿¨ÅÆÊÓÍ¼
        CardView* topCardView = stackView->popTrayCard();
        if (topCardView) {
            topCardView->removeFromParent();
        }

        stackView->pushTrayCard(destCard, false);
    }
}

void UndoService::undoDrawStack(const OperationRecord& record, GameModel* gameModel, StackController* stackController) {
    if (!gameModel || !stackController) {
        return;
    }

    CardModel currentTopCard = gameModel->popTrayCard();

    gameModel->addStackCard(currentTopCard);

    CardModel destCard = record.destinationCard;
    destCard.setPosition(record.destinationPosition);
    gameModel->pushTrayCard(destCard);

    StackView* stackView = stackController->getView();

    if (stackView) {
        CardView* topCardView = stackView->popTrayCard();
        if (topCardView) {
            topCardView->removeFromParent();
        }

        stackView->addStackCard(currentTopCard);

        stackView->pushTrayCard(destCard, false);
    }
}