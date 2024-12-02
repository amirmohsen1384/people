#include "include/dialogs/personeditor.h"
#include "include/application.h"
#include "ui_application.h"
#include <QFileDialog>
#include <QFile>

Application::Application(QWidget *parent) : QMainWindow(parent), ui(new Ui::Application) {
    ui->setupUi(this);
}

void Application::Add() {
    PersonEditor editor(this);
    if(editor.exec() == QDialog::Accepted) {
        model.Append(editor.GetPerson());
    }
}

void Application::Save() {
    const QString &filename = this->windowFilePath();
    if(filename.isEmpty()) {
        this->SaveAs();
    } else {
        this->Save(filename);
    }
}

void Application::Clear() {
    model.Clear();
}

void Application::SaveAs() {
    static QStringList history = {};
    QFileDialog dialog(this);
    dialog.setHistory(history);
    dialog.setDefaultSuffix(".pf");
    dialog.setDirectory(QDir::home());
    dialog.setNameFilter("People files (*.pf)");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::ExistingFile);
    if(dialog.exec() == QDialog::Accepted) {
        const QString &filename = dialog.selectedFiles().constFirst();
        if(this->Save(filename) == true) {
            history.append(filename);
        }
    }
}



void Application::Edit(const QModelIndex &index) {
    if(!index.isValid()) {
        return;
    }
    PersonEditor editor(model.Obtain(index), this);
    if(editor.exec() == QDialog::Accepted) {
        model.Modify(index, editor.GetPerson());
    }
}

void Application::Delete(const QModelIndexList &indices) {
    model.Remove(indices);
}

Application::~Application()
{
    delete ui;
}

constexpr quint64 magic = 0x419A1FC8;

bool Application::Load(const QString &filename) {

    // Open a file with the specified filename
    QFile file(filename);
    if(!file.open(QFile::ReadOnly)) {
        return false;
    }
    QDataStream stream(&file);

    // Read the magic number from the file
    quint64 value = 0;
    stream >> value;

    // Check if the file is valid to be read
    if(value != magic) {
        return false;
    }

    // Start reading the file
    PersonList container;
    stream >> container;

    // Update the model with the read list
    model.SetContainer(container);

    return true;
}

bool Application::Save(const QString &filename) {

    // Open a file with the specified filename
    QFile file(filename);
    if(!file.open(QFile::WriteOnly)) {
        return false;
    }
    QDataStream stream(&file);

    // Write the magic number to the file
    stream << magic;

    // Write the list being represented by the list
    stream << model.GetContainer();

    // Update the current filename
    this->setWindowFilePath(filename);

    return true;
}
