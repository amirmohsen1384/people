#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QDate>
#include <QPixmap>
#include <QDataStream>

class Person : public QObject
{
public:
    enum class Gender {
        Male,
        Female
    };

private:
    Q_OBJECT
    QString     firstName;
    QString     lastName;
    Gender      gender = Gender::Male;
    QDate       birthday = QDate::currentDate();
    QPixmap     photo;
    QDateTime   creation = QDateTime::currentDateTime();
    QDateTime   lastModification = QDateTime::currentDateTime();

private slots:
    void UpdateLastModification();

public:
    explicit Person(QObject *parent = nullptr);
    Person& operator=(const Person &another);
    Person(const Person &another, QObject *parent = nullptr);

    QString GetFirstName() const;
    void SetFirstName(const QString &value);

    QString GetLastName() const;
    void SetLastName(const QString &value);

    Gender GetGender() const;
    void SetGender(const Gender &value);

    QDate GetBirthday() const;
    void SetBirthday(const QDate &value);

    QPixmap GetPhoto() const;
    void SetPhoto(const QPixmap &value);

    QDateTime GetLastModification() const;
    QDateTime GetCreation() const;

    QString GetFullName() const;

    friend QDataStream& operator<<(QDataStream &stream, const Person &data);
    friend QDataStream& operator>>(QDataStream &stream, Person &data);
    friend QDebug operator<<(QDebug debugger, const Person &data);

signals:
    void FirstNameChanged(const QString &value);
    void LastNameChanged(const QString &value);
    void GenderChanged(const Gender &value);
    void BirthdayChanged(const QDate &value);
    void PhotoChanged(const QPixmap &value);
    void LastModificationChanged(const QDateTime &value);
};

typedef QList<Person> PersonList;
typedef QListIterator<Person> PersonListIterator;

Q_DECLARE_METATYPE(Person)

#endif // PERSON_H
