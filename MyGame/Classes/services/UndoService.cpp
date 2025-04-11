#include "UndoService.h"  

void UndoService::undoMatchPlayfield(const OperationRecord& record, GameModel* gameModel,
    PlayFieldController* playFieldController, StackController* stackController) {
    if (!gameModel || !playFieldController || !stackController) {
        return;
    }

    // �ָ�����������
    CardModel sourceCard = record.sourceCard;
    sourceCard.setPosition(record.sourcePosition);
    gameModel->addPlayfieldCard(sourceCard);

    // �ָ����ƶѿ���
    CardModel destCard = record.destinationCard;
    destCard.setPosition(record.destinationPosition);

    // �Ƴ���ǰ���ƶѶ�������
    gameModel->popTrayCard();

    // �������ԭ���ƶѶ�������
    gameModel->pushTrayCard(destCard);

    // ������ͼ
    PlayFieldView* playFieldView = playFieldController->getView();
    StackView* stackView = stackController->getView();

    if (playFieldView && stackView) {
        // ���������������ͼ
        playFieldView->addCard(sourceCard);

        // �Ƴ����滻���ƶѶ���������ͼ
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