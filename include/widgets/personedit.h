#ifndef PERSONEDIT_H
#define PERSONEDIT_H
#include <QWidget>
#include "include/data/person.h"
#include "include/camera/photographer.h"

namespace Ui { class PersonEdit; }

class PersonEdit : public QWidget
{
    Q_OBJECT
    Ui::PersonEdit *ui = nullptr;
    Photographer photographer;
    Person initial;

protected:
    virtual void closeEvent(QCloseEvent *event) override;

protected slots:
    void UpdatePhotographerControl();
    void NotifyImageBrowser();
    QImage FindImageFile();

public:
    explicit PersonEdit(const Person & initial, QWidget *parent = nullptr);
    explicit PersonEdit(QWidget *parent = nullptr);
    ~PersonEdit();

    Person::Gender GetGender() const;
    Person GetInitialPerson() const;
    QString GetFirstName() const;
    QString GetLastName() const;
    QDate GetBirthday() const;
    Person GetPerson() const;
    QImage GetPhoto() const;

public slots:
    void SetFirstName(const QString &value);
    void ResetFirstName();

    void SetLastName(const QString &value);
    void ResetLastName();

    void SetBirthday(const QDate &value);
    void ResetBirthday();

    void SetGender(const Person::Gender &value);
    void ResetGender();

    void SetPhoto(const QImage &value);
    void ResetPhoto();

    void SetPerson(const Person &value);
    void ResetPerson();

signals:
    void FirstNameChanged(const QString &value);
    void LastNameChanged(const QString &value);
    void BirthdayChanged(const QDate &value);
    void GenderChanged(const Person::Gender &value);
    void PhotoChanged(const QImage &value);
    void FirstNameRejected();
    void LastNameRejected();
};

#endif // PERSONEDIT_H
