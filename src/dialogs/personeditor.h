#ifndef PERSONEDITOR_H
#define PERSONEDITOR_H

#include "include/dialogs/abstractinterface.h"
#include "include/data/person.h"

namespace Ui {
class PersonEditor;
}

class PersonEditor : public AbstractInterface
{
    Q_OBJECT
    Ui::PersonEditor *ui = nullptr;

protected slots:
    virtual void UpdateTitle() override;

public:
    explicit PersonEditor(const Person &info, QWidget *parent = nullptr);
    explicit PersonEditor(QWidget *parent = nullptr);
    virtual Person GetPerson() const override;
    ~PersonEditor();

public slots:
    void SetPerson(const Person &person);
    virtual void accept() override;

signals:
    void PersonChanged(const Person &person);

};

#endif // PERSONEDITOR_H
