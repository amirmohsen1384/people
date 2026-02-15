#ifndef PERSONEDIT_H
#define PERSONEDIT_H
#include <QWidget>
#include <QCameraDevice>
#include <QMediaDevices>
#include "data/person.h"

namespace Ui { class PersonEdit; }

class PersonEdit : public QWidget
{
    Q_OBJECT
    Ui::PersonEdit *ui = nullptr;
    QMediaDevices devices;
    Person initial;

protected slots:
    void UpdatePhotographerControl();
    void NotifyImageBrowser();
    void NotifyPhotographer();
    QImage FindImageFile();

public:
    explicit PersonEdit(const Person & initial, QWidget *parent = nullptr);
    explicit PersonEdit(QWidget *parent = nullptr);
    ~PersonEdit();

    Person::Gender GetGender() const;
    QString GetFirstName() const;
    QString GetLastName() const;
    QDate GetBirthday() const;
    Person GetInitial() const;
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

    void SetInitial(const Person &value);

signals:
    void FirstNameChanged(const QString &value);
    void LastNameChanged(const QString &value);
    void BirthdayChanged(const QDate &value);
    void InitialChanged(const Person &value);
    void GenderChanged(const Person::Gender &value);
    void PhotoChanged(const QImage &value);
    void FirstNameRejected();
    void LastNameRejected();

};

#endif // PERSONEDIT_H
