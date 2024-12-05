#ifndef SAVEREQUIREMENT_H
#define SAVEREQUIREMENT_H

#include <QObject>
#include <QMessageBox>

class SaveRequirement : public QObject
{
    Q_OBJECT
    bool required;

public:
    explicit SaveRequirement(bool initial = false, QObject *parent = nullptr);
    bool IsRequired() const;

public slots:
    void SetRequired(bool state);
    QMessageBox::ButtonRole Notify(QWidget *parent);

signals:
    void StateChanged(bool requirement);
};

#endif // SAVEREQUIREMENT_H
