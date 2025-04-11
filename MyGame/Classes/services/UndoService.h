#ifndef UNDO_SERVICE_H  
#define UNDO_SERVICE_H  

#include "models/UndoModel.h"  
#include "models/GameModel.h"  
#include "controllers/PlayFieldController.h"  
#include "controllers/StackController.h"  

// ���˷���
class UndoService {
public:
    // ����ƥ�����
    static void undoMatchPlayfield(const OperationRecord& record, GameModel* gameModel,
        PlayFieldController* playFieldController, StackController* stackController);

    // ���˳��Ʋ���
    static void undoDrawStack(const OperationRecord& record, GameModel* gameModel, StackController* stackController);
};

#endif