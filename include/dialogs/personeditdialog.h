#ifndef PERSONEDITDIALOG_H
#define PERSONEDITDIALOG_H

#include <QDialog>
#include "include/data/person.h"

namespace Ui {
class PersonEditDialog;
}

class PersonEditDialog : public QDialog
{
    Q_OBJECT
    Ui::PersonEditDialog *ui = nullptr;

public:
    explicit PersonEditDialog(const Person &info, QWidget *parent = nullptr);
    explicit PersonEditDialog(QWidget *parent = nullptr);
    Person GetPerson() const;
    ~PersonEditDialog();

public slots:
    void SetPerson(const Person &person);
    virtual void accept() override;

signals:
    void PersonChanged(const Person &person);

};

#endif // PERSONEDITDIALOG_H
