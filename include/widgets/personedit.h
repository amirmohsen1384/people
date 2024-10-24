#ifndef PERSONEDIT_H
#define PERSONEDIT_H
#include <QWidget>
#include <QPointer>
#include "include/data/person.h"
#include "include/camera/photographer.h"

namespace Ui { class PersonEdit; }

class PersonEdit : public QWidget
{
    Q_OBJECT
    QPointer<Person> initial = nullptr;
    Ui::PersonEdit *ui = nullptr;
    Photographer photographer;
private:
    QImage FindImageFile();

protected:
    virtual void closeEvent(QCloseEvent *event) override;

protected slots:
    void UpdatePhotographerControl();
    void NotifyPhotographer();
    void NotifyImageBrowser();

public:
    explicit PersonEdit(QWidget *parent = nullptr);
    explicit PersonEdit(QPointer<Person> initial, QWidget *parent = nullptr);

    QString GetFirstName() const;

    QString GetLastName() const;

    QDate GetBirthday() const;

    Person::Gender GetGender() const;

    QImage GetPhoto() const;

    QPointer<Person> GetPerson() const;

    const QPointer<Person> GetInitialPerson() const;
    ~PersonEdit();

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

    void SetPerson(const QPointer<Person> &value);
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
