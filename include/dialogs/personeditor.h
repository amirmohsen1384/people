#ifndef PERSONEDITOR_H
#define PERSONEDITOR_H

#include <QDialog>
#include "include/data/person.h"

namespace Ui {
class PersonEditor;
}

class PersonEditor : public QDialog
{
    const QSize size = QSize(900, 900);
    Ui::PersonEditor *ui = nullptr;
    Q_OBJECT

protected:
    virtual QSize sizeHint() const;

protected slots:
    void UpdateTitle();

public:
    explicit PersonEditor(const Person &info, QWidget *parent = nullptr);
    explicit PersonEditor(QWidget *parent = nullptr);
    Person GetPerson() const;
    ~PersonEditor();

public slots:
    void SetPerson(const Person &person);
    virtual void accept() override;

signals:
    void PersonChanged(const Person &person);

};

#endif // PERSONEDITOR_H
