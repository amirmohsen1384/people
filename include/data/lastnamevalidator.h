#ifndef LASTNAMEVALIDATOR_H
#define LASTNAMEVALIDATOR_H

#include <QValidator>

class LastNameValidator : public QValidator
{
    Q_OBJECT
public:
    explicit LastNameValidator(QObject *parent = nullptr) : QValidator(parent) {}

    virtual QValidator::State validate(QString &input, int &pos) const override;
};

#endif // LASTNAMEVALIDATOR_H
