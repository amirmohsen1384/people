#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QDate>
#include <QImage>
#include <QDataStream>

class PersonEdit;

class Person : public QObject
{
public:
    enum class Gender {
        Male,
        Female
    };
    Q_ENUM(Gender)

    enum Role {
        LastModificationRole = 512,
        FirstNameRole,
        LastNameRole,
        BirthdayRole,
        CreationRole,
        PersonRole,
        GenderRole,
        PhotoRole,
        NameRole,
        AgeRole
    };
    Q_ENUM(Role)

private:
    Q_OBJECT
    QString     firstName;
    QString     lastName;
    Gender      gender = Gender::Male;
    QDate       birthday = QDate::currentDate();
    QImage      photo;
    QDateTime   creation = QDateTime::currentDateTime();
    QDateTime   lastModification = QDateTime::currentDateTime();

private slots:
    void UpdateLastModification();

public:
    Person(QObject *parent = nullptr);
    Person& operator=(const Person &another);
    Person(const Person &another, QObject *parent = nullptr);

    QString GetFirstName() const;
    void SetFirstName(const QString &value);

    QString GetLastName() const;
    void SetLastName(const QString &value);

    Person::Gender GetGender() const;
    void SetGender(const Gender &value);

    QDate GetBirthday() const;
    void SetBirthday(const QDate &value);

    QImage GetPhoto() const;
    void SetPhoto(const QImage &value);

    QDateTime GetLastModification() const;
    QDateTime GetCreation() const;

    QString GetFullName() const;

    friend QDataStream& operator<<(QDataStream &stream, const Person &data);
    friend QDataStream& operator>>(QDataStream &stream, Person &data);
    friend QDebug operator<<(QDebug debugger, const Person &data);
    friend class PersonEdit;

signals:
    void FirstNameChanged(const QString &value);
    void LastNameChanged(const QString &value);
    void GenderChanged(const Gender &value);
    void BirthdayChanged(const QDate &value);
    void PhotoChanged(const QImage &value);
    void LastModificationChanged(const QDateTime &value);
};

using PersonList = QList<Person>;
using PersonListIterator = QListIterator<Person>;

Q_DECLARE_METATYPE(Person)

#endif // PERSON_H
