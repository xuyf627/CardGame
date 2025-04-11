#ifndef UNDO_MANAGER_H  
#define UNDO_MANAGER_H  

#include "models/UndoModel.h"  
#include <memory>  

// ���˹�����
class UndoManager {
public:
    UndoManager();

    void init();

    // ��¼����
    void recordOperation(const OperationRecord& record);

    // ��ȡ���Ƴ�����Ĳ�����¼
    OperationRecord undoLastOperation();

    void clear();

    bool canUndo() const;

private:
    std::unique_ptr<UndoModel> _undoModel;
};

#endif