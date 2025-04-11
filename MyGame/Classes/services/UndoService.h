#ifndef UNDO_SERVICE_H  
#define UNDO_SERVICE_H  

#include "models/UndoModel.h"  
#include "models/GameModel.h"  
#include "controllers/PlayFieldController.h"  
#include "controllers/StackController.h"  

// 回退服务
class UndoService {
public:
    // 回退匹配操作
    static void undoMatchPlayfield(const OperationRecord& record, GameModel* gameModel,
        PlayFieldController* playFieldController, StackController* stackController);

    // 回退抽牌操作
    static void undoDrawStack(const OperationRecord& record, GameModel* gameModel, StackController* stackController);
};

#endif