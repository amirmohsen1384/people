#ifndef PERSONEDITDIALOG_H
#define PERSONEDITDIALOG_H

#include <QDialog>
#include "include/data/person.h"

namespace Ui {
class PersonEditDialog;
}

class PersonEditDialog : public QDialog
{
    const QSize fixedSize = QSize(1000, 900);
    Ui::PersonEditDialog *ui = nullptr;
    Q_OBJECT

protected:
    virtual QSize sizeHint() const;

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
