#include "include/dialogs/personeditor.h"
#include "include/dialogs/personviewer.h"
#include "include/application.h"
#include "ui_application.h"

void Application::Add() {
    PersonEditor editor(this);
    if(editor.exec() == QDialog::Accepted) {
        model.Append(editor.GetPerson());
        save.SetRequired(true);
    }
}
void Application::Clear() {
    switch(save.Request()) {
    case SaveRequest::SaveFirst: {
        this->Save();
        break;
    }
    case SaveRequest::Rejected: {
        return;
    }
    }
    model.Clear();
}

void Application::Edit(const QModelIndex &index) {
    if(!index.isValid()) {
        return;
    }
    PersonEditor editor(model.Obtain(index), this);
    if(editor.exec() == QDialog::Accepted) {
        model.Modify(index, editor.GetPerson());
        save.SetRequired(true);
    }
}

void Application::View(const QModelIndex &index) {
    if(!index.isValid()) {
        return;
    }
    PersonViewer viewer(model.Obtain(index), this);
    connect(&viewer, &PersonViewer::EditRequested, this, [&]() {
        PersonEditor editor(model.Obtain(index), &viewer);
        if(editor.exec() == QDialog::Accepted) {
            model.Modify(index, editor.GetPerson());
            viewer.SetPerson(model.Obtain(index));
            save.SetRequired(true);
        }
    });
    viewer.exec();
}
void Application::Delete(QModelIndexList &indices) {
    if(!indices.isEmpty()) {
        model.Remove(indices);
        save.SetRequired(true);
    }
}
void Application::Delete() {
    QModelIndexList indices = ui->container->selectionModel()->selectedIndexes();
    QMessageBox message(this);
    message.setWindowTitle("Caution");
    message.setIcon(QMessageBox::Warning);
    message.setInformativeText("This operation is permanent and cannot be restored.");
    message.setText(QString("Are you sure to delete %1 item(s) from the list?").arg(indices.size()));
    message.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if(message.exec() == QMessageBox::Yes) {
        this->Delete(indices);
    }
}
void Application::Edit() {
    this->Edit(ui->container->currentIndex());
}

void Application::View() {
    const QModelIndex &index = ui->container->currentIndex();
    this->View(index);
}
