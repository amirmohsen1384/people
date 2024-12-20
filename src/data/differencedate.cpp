#include "include/data/differencedate.h"


DifferenceDate::DifferenceDate(int year, int month, int day) {
    this->SetDay(day);
    this->SetYear(year);
    this->SetMonth(month);
}

DifferenceDate::DifferenceDate(const DifferenceDate &object) {
    *this = object;
}

DifferenceDate &DifferenceDate::operator=(const DifferenceDate &another) {
    this->SetDay(another.GetDay());
    this->SetYear(another.GetYear());
    this->SetMonth(another.GetMonth());
    return *this;
}

QDataStream &operator<<(QDataStream &stream, const DifferenceDate &data) {
    stream << data.year << data.month << data.day;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, DifferenceDate &data) {
    stream >> data.year >> data.month >> data.day;
    return stream;
}

int DifferenceDate::GetDay() const {
    return day;
}

void DifferenceDate::SetDay(int day) {
    this->day = day;
}

int DifferenceDate::GetYear() const {
    return year;
}

void DifferenceDate::SetYear(int year) {
    this->year = year;
}

int DifferenceDate::GetMonth() const {
    return month;
}

void DifferenceDate::SetMonth(int month) {
    this->month = month;
}

DifferenceDate DifferenceDate::GetDifference(const QDate &d1, const QDate &d2) {
    QDate earlier, later;
    if(d1 < d2) {
        earlier = d1;
        later = d2;

    } else {
        earlier = d2;
        later = d1;

    }

    DifferenceDate result;
    if(later.day() < earlier.day()) {
        result.day = later.day() + later.daysInMonth();
        result.month = later.month() - 1;
    }
    result.day -= earlier.day();

    if(result.month < earlier.month()) {
        result.month = later.month() + 12;
        result.year = later.year() - 1;
    }
    result.month -= earlier.month();
    result.year = later.year() - earlier.year();

    return result;
}

DifferenceDate DifferenceDate::GetDifference(const QDate &d1) {
    return GetDifference(d1, QDate::currentDate());
}

bool operator<(const DifferenceDate &one, const DifferenceDate &two) {
    if(one.year > two.year) {
        return false;

    } else if(one.year < two.year) {
        return true;
    }
    else {
        if(one.month > two.month) {
            return false;

        } else if(one.month < two.month) {
            return true;

        }
        else {
            if(one.day > two.day) {
                return false;

            } else if(one.day < two.day) {
                return true;

            } else {
                return false;
            }
        }
    }
}

bool operator>=(const DifferenceDate &one, const DifferenceDate &two) {
    return !(one < two);
}

bool operator>(const DifferenceDate &one, const DifferenceDate &two) {
    if(one.year > two.year) {
        return true;

    } else if(one.year < two.year) {
        return false;
    }
    else {
        if(one.month > two.month) {
            return true;

        } else if(one.month < two.month) {
            return false;

        }
        else {
            if(one.day > two.day) {
                return true;

            } else if(one.day < two.day) {
                return true;

            } else {
                return false;
            }
        }
    }
}

bool operator<=(const DifferenceDate &one, const DifferenceDate &two) {
    return !(one > two);
}

bool operator==(const DifferenceDate &one, const DifferenceDate &two) {
    return (one.year == two.year) && (one.month == two.month) && (one.day == two.day);
}

bool operator!=(const DifferenceDate &one, const DifferenceDate &two) {
    return !(one == two);
}
QDebug operator<<(QDebug debugger, const DifferenceDate &date) {
    debugger << date.year << " year(s), ";
    debugger << date.month << " month(s), ";
    debugger << date.day << " day(s)";
    return debugger;
}
