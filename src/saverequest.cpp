#include "include/saverequest.h"

SaveRequest::SaveRequest(bool initial, QObject *parent) :
    QObject{parent},
    required{initial} {}

bool SaveRequest::IsRequired() const {
    return required;
}
void SaveRequest::SetRequired(bool state) {
    required = state;
    emit StateChanged(state);
}

SaveRequest::Result SaveRequest::Request(QWidget *parent) {
    if(!IsRequired()) {
        return Result::NotRequired;
    }
    QMessageBox dialog(parent);
    dialog.setWindowTitle("Save Changes");
    dialog.setIcon(QMessageBox::Information);
    dialog.setInformativeText("Do you want to save changes to a file?");
    dialog.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch(dialog.exec()) {
    case QMessageBox::Save: {
        return Result::SaveFirst;
    }
    case QMessageBox::Discard: {
        return Result::DiscardFirst;
    }
    case QMessageBox::Cancel: {
        return Result::Rejected;
    }
    default: {
        return Result::Unknown;
    }
    }
}
