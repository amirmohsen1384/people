#ifndef PERSONVIEWER_H
#define PERSONVIEWER_H

#include "include/dialogs/abstractinterface.h"
#include "include/data/person.h"

namespace Ui {
class PersonViewer;
}

class PersonViewer : public AbstractInterface
{
    Q_OBJECT
    Ui::PersonViewer *ui = nullptr;

protected slots:
    void RequestToEdit();
    virtual void UpdateTitle() override;

public:
    explicit PersonViewer(const Person &person, QWidget *parent = nullptr);
    explicit PersonViewer(QWidget *parent = nullptr);
    virtual Person GetPerson() const override;
    ~PersonViewer();

public slots:
    void SetPerson(const Person &person);

signals:
    void PersonChanged(const Person &data);
    void EditRequested(const Person &data);

};

#endif // PERSONVIEWER_H
