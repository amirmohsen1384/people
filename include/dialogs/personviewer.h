#ifndef PERSONVIEWER_H
#define PERSONVIEWER_H

#include <QDialog>
#include "include/data/person.h"

namespace Ui {
class PersonViewer;
}

class PersonViewer : public QDialog
{
    Q_OBJECT
    const QSize size = QSize(900, 900);
    Ui::PersonViewer *ui = nullptr;

protected:
    virtual QSize sizeHint() const;

protected slots:
    void UpdateTitle();
    void RequestToEdit();

public:
    explicit PersonViewer(const Person &person, QWidget *parent = nullptr);
    explicit PersonViewer(QWidget *parent = nullptr);
    ~PersonViewer();

    Person GetPerson() const;

public slots:
    void SetPerson(const Person &person);

signals:
    void PersonChanged(const Person &data);
    void EditRequested(const Person &data);

};

#endif // PERSONVIEWER_H
