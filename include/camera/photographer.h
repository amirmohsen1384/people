#ifndef PHOTOGRAPHER_H
#define PHOTOGRAPHER_H

#include <QDialog>
#include <QCamera>
#include <QImageCapture>
#include <QMediaCaptureSession>

namespace Ui {
class Photographer;
}

class Photographer : public QDialog
{
    Q_OBJECT
    QCamera camera;
    QImageCapture capture;
    QMediaCaptureSession session;
    Ui::Photographer *ui = nullptr;

private:
    void Initialize();

public:
    explicit Photographer(QWidget *parent = nullptr);
    ~Photographer();
};

#endif // PHOTOGRAPHER_H
