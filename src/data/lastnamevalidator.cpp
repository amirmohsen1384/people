#include "../../include/data/lastnamevalidator.h"

QValidator::State LastNameValidator::validate(QString &input, int &pos) const {
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
