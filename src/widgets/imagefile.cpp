#include "include/widgets/personedit.h"
#include "ui_personedit.h"
#include <QImageReader>
#include <QFileDialog>

// This function is used to return a list of supported filter used in image file dialog
QStringList SupportedImageFilters() {
    QStringList container = {};
    container.append("JPEG files (*.jpg *.jpeg)");
    container.append("PNG files (*.png)");
    container.append("BMP files (*.bmp)");
    return container;
}

// This function is used to create a image file dialog and open one
QImage PersonEdit::FindImageFile() {
    QFileDialog dialog(this);
    static QStringList history = {};

    dialog.setWindowTitle("Select a photo to open");
    dialog.setNameFilters(SupportedImageFilters());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::List);
    dialog.setDirectory(QDir::home());
    dialog.setHistory(history);

    if(dialog.exec() == QDialog::Accepted) {
        QImageReader reader(dialog.selectedFiles().constFirst());
        return reader.read();

    } else {
        return QImage();

    }
}
QPixmap PersonEdit::GetDefaultPhoto() const {
    return QPixmap(":/images/default.png");

}
void PersonEdit::LoadImage(const QImage &image) {
    if(image.isNull()) {
        this->SetPhoto(QPixmap());
    }
}
