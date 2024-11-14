#ifndef PERSONVIEWER_H
#define PERSONVIEWER_H

#include <QDialog>

namespace Ui {
class PersonViewer;
}

class PersonViewer : public QDialog
{
    Q_OBJECT
    Ui::PersonViewer *ui = nullptr;
public:
    explicit PersonViewer(QWidget *parent = nullptr);
    ~PersonViewer();
};

#endif // PERSONVIEWER_H
