#include "include/application.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDataStream>
#include <QFile>

void Application::New() {
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

void Application::Close() {
    switch(save.Request()) {
    case SaveRequest::SaveFirst: {
        this->Save();
        break;
    }
    case SaveRequest::Rejected: {
        return;
    }
    }
    this->close();
}

void Application::Open() {
    // Construct required objects
    static QStringList history = {};
    QFileDialog dialog(this);

    // Customize the dialog
    dialog.setHistory(history);
    dialog.setDefaultSuffix(".pf");
    dialog.setDirectory(QDir::home());
    dialog.setNameFilter("People files (*.pf)");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);

    // Execute the dialog
    if(dialog.exec() == QDialog::Accepted) {

        // Save the model if needed
        switch(save.Request(this)) {
        case SaveRequest::SaveFirst: {
            this->Save();
            break;
        }
        case SaveRequest::DiscardFirst: {
            model.Clear();
            break;
        }
        case SaveRequest::Rejected: {
            return;
        }
        default: {
            // Load information from the file
            const QString filename = dialog.selectedFiles().constFirst();
            if(this->Load(filename)) {
                history.append(filename);
            }
        }
        }
    }
}

bool Application::Save() {
    // Get the window file path
    const QString filename = this->windowFilePath();

    // Start saving the file based on the existing filename
    if(filename.isEmpty()) {
        return this->SaveAs();
    } else {
        return this->Save(filename);
    }
}

bool Application::SaveAs() {
    // Construct the required objects
    QFileDialog dialog(this);
    static QStringList history = {};

    // Customize the dialog
    dialog.setHistory(history);
    dialog.setDefaultSuffix(".pf");
    dialog.setDirectory(QDir::home());
    dialog.setNameFilter("People files (*.pf)");
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    // Execute the dialog
    if(dialog.exec() == QDialog::Accepted) {
        const QString filename = dialog.selectedFiles().constFirst();
        if(this->Save(filename)) {
            history.append(filename);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
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

    // Update the information
    save.SetRequired(false);
    this->setWindowFilePath(filename);

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

    // Update the information
    save.SetRequired(false);
    this->setWindowFilePath(filename);

    return true;
}
