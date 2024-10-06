#ifndef FIRSTNAMEVALIDATOR_H
#define FIRSTNAMEVALIDATOR_H

#include <QValidator>

class FirstNameValidator : public QValidator
{
    Q_OBJECT
public:
    explicit FirstNameValidator(QObject *parent = nullptr) : QValidator(parent) {}

    virtual QValidator::State validate(QString &input, int &pos) const override;
};

#endif // FIRSTNAMEVALIDATOR_H
