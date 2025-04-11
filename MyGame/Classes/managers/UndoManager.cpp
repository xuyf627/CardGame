#include "UndoManager.h"  

UndoManager::UndoManager() : _undoModel(new UndoModel()) {
}

void UndoManager::init() {
    _undoModel->clear();
}

void UndoManager::recordOperation(const OperationRecord& record) {
    _undoModel->addRecord(record);
}

OperationRecord UndoManager::undoLastOperation() {
    return _undoModel->popRecord();
}

void UndoManager::clear() {
    _undoModel->clear();
}

bool UndoManager::canUndo() const {
    return _undoModel->canUndo();
}