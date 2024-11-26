#include "include/data/differencedate.h"


DifferenceDate::DifferenceDate(int year, int month, int date) {
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

QDataStream &DifferenceDate::operator<<(QDataStream &stream, const DifferenceDate &data) {
    stream << data.year << data.month << data.day;
    return stream;
}

QDataStream &DifferenceDate::operator>>(QDataStream &stream, DifferenceDate &data) {
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
        later.setDate(later.year(), later.month() - 1, later.day() + later.daysInMonth());
    }
    result.day = later.day() - earlier.day();

    if(later.month() < earlier.month()) {
        later.setDate(later.year() - 1, later.month() + 12, later.day());
    }
    result.month = later.month() - earlier.month();

    result.year = later.year() - earlier.year();

    return later;
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
