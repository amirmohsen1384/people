#ifndef PERSONVIEW_H
#define PERSONVIEW_H
#include <QWidget>

namespace Ui {
class PersonView;
}

class PersonView : public QWidget
{
    Q_OBJECT
    Ui::PersonView *ui = nullptr;

public:
    explicit PersonView(QWidget *parent = nullptr);
    ~PersonView();
};

#endif // PERSONVIEW_H
