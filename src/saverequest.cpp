#include "include/saverequirement.h"

SaveRequirement::SaveRequirement(bool initial, QObject *parent) :
    QObject{parent},
    required{initial}
{}

bool SaveRequirement::IsRequired() const {
    return required;
}

void SaveRequirement::SetRequired(bool state) {
    required = state;
    emit stateChanged(state);
}

QMessageBox::ButtonRole SaveRequirement::Notify(QWidget *parent) {
    QMessageBox dialog(parent);
    dialog.setWindowTitle("Save Changes");
    dialog.setIcon(QMessageBox::Information);
    dialog.setInformativeText("Do you want to save changes to a file?");
    dialog.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    dialog.exec();
    return dialog.result();
}
