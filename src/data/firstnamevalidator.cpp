#include "../../include/data/firstnamevalidator.h"

// This function checks whether the string contains only letters and whitespaces.
QValidator::State FirstNameValidator::validate(QString &input, int &pos) const {
    if(input.isEmpty()) {
        return QValidator::Acceptable;

    } else {
        const QChar &character = input.at(pos - 1);
        if(character.isDigit() || character.isSymbol() || character.isPunct()) {
            return QValidator::Invalid;

        } else if(character.isSpace()) {
            return QValidator::Intermediate;

        } else {
            return QValidator::Acceptable;

        }

    }
}
