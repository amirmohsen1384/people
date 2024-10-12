#ifndef PHOTOGRAPHER_H
#define PHOTOGRAPHER_H

#include <QDialog>

namespace Ui {
class Photographer;
}

class Photographer : public QDialog
{
    Q_OBJECT
    Ui::Photographer *ui = nullptr;

public:
    explicit Photographer(QWidget *parent = nullptr);
    ~Photographer();
};

#endif // PHOTOGRAPHER_H
