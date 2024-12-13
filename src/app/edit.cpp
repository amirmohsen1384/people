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
    this->Delete(indices);
}
void Application::Edit() {
    this->Edit(ui->container->currentIndex());
}

void Application::View() {
    const QModelIndex &index = ui->container->currentIndex();
    this->View(index);
}
