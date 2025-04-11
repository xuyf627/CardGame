#include "UndoModel.h"  

UndoModel::UndoModel() {
}

void UndoModel::addRecord(const OperationRecord& record) {
    _operations.push_back(record);
}

OperationRecord UndoModel::popRecord() {
    if (_operations.empty()) {
        return OperationRecord();
    }

    OperationRecord record = _operations.back();
    _operations.pop_back();
    return record;
}

void UndoModel::clear() {
    _operations.clear();
}

bool UndoModel::canUndo() const {
    return !_operations.empty();
}