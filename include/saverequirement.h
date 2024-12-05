#ifndef SAVEREQUIREMENT_H
#define SAVEREQUIREMENT_H

#include <QObject>

class SaveRequirement : public QObject
{
    Q_OBJECT
public:
    explicit SaveRequirement(QObject *parent = nullptr);
};

#endif // SAVEREQUIREMENT_H
