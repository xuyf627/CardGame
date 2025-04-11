#ifndef UNDO_MANAGER_H  
#define UNDO_MANAGER_H  

#include "models/UndoModel.h"  
#include <memory>  

// 回退管理类
class UndoManager {
public:
    UndoManager();

    void init();

    // 记录操作
    void recordOperation(const OperationRecord& record);

    // 获取并移除最近的操作记录
    OperationRecord undoLastOperation();

    void clear();

    bool canUndo() const;

private:
    std::unique_ptr<UndoModel> _undoModel;
};

#endif