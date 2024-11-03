#ifndef PERSONVIEW_H
#define PERSONVIEW_H

#include "include/data/person.h"
#include <QWidget>

namespace Ui {
class PersonView;
}

class PersonView : public QWidget
{
    Q_OBJECT
    Person information;
    Ui::PersonView *ui = nullptr;

private slots:
    void UpdatePerson();

private slots:
    void UpdateName();
    void UpdatePhoto();
    void UpdateGender();
    void UpdateBirthday();
    void UpdateCreation();
    void UpdateLastModification();

public:
    explicit PersonView(QWidget *parent = nullptr);
    explicit PersonView(const Person &value, QWidget *parent = nullptr);
    ~PersonView();

    Person GetPerson() const;

public slots:
    void SetPerson(const Person &data);

signals:
    void PersonChanged(const Person &data);
};

#endif // PERSONVIEW_H
