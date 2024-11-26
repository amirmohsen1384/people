#ifndef DIFFERENCEDATE_H
#define DIFFERENCEDATE_H

#include <QDate>
#include <QVariant>
#include <QDataStream>

class DifferenceDate
{
    int year;
    int month;
    int day;

public:
    DifferenceDate() : year(0), month(0), day(0) {}
    DifferenceDate(int year, int month, int day);
    DifferenceDate(const DifferenceDate &object);

    DifferenceDate& operator=(const DifferenceDate &another);

    friend QDataStream& operator<<(QDataStream &stream, const DifferenceDate &data);
    friend QDataStream& operator>>(QDataStream &stream, DifferenceDate &data);
    friend QDebug operator<<(QDebug debugger, const DifferenceDate &date);

    int GetDay() const;
    void SetDay(int day);

    int GetYear() const;
    void SetYear(int year);

    int GetMonth() const;
    void SetMonth(int month);

    friend bool operator<(const DifferenceDate &one, const DifferenceDate &two);
    friend bool operator>(const DifferenceDate &one, const DifferenceDate &two);
    friend bool operator<=(const DifferenceDate &one, const DifferenceDate &two);
    friend bool operator>=(const DifferenceDate &one, const DifferenceDate &two);
    friend bool operator==(const DifferenceDate &one, const DifferenceDate &two);
    friend bool operator!=(const DifferenceDate &one, const DifferenceDate &two);

    static DifferenceDate GetDifference(const QDate &d1, const QDate &d2);
    static DifferenceDate GetDifference(const QDate &d1);
};

Q_DECLARE_METATYPE(DifferenceDate)

QDataStream& operator<<(QDataStream &stream, const DifferenceDate &data);
QDataStream& operator>>(QDataStream &stream, DifferenceDate &data);
QDebug operator<<(QDebug debugger, const DifferenceDate &date);

bool operator<(const DifferenceDate &one, const DifferenceDate &two);
bool operator>(const DifferenceDate &one, const DifferenceDate &two);
bool operator<=(const DifferenceDate &one, const DifferenceDate &two);
bool operator>=(const DifferenceDate &one, const DifferenceDate &two);
bool operator==(const DifferenceDate &one, const DifferenceDate &two);
bool operator!=(const DifferenceDate &one, const DifferenceDate &two);

#endif // DIFFERENCEDATE_H
