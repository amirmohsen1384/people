#ifndef ABSTRACTINTERFACE_H
#define ABSTRACTINTERFACE_H

#include "include/data/person.h"
#include <QMargins>
#include <QDialog>
#include <QScreen>

class AbstractInterface : public QDialog
{
    Q_OBJECT
    QScreen *screen = nullptr;

protected:
    virtual QMargins EvaluateMargins() const;
    virtual QSize sizeHint() const override;
    virtual void UpdateWindow();

protected slots:
    virtual void UpdateTitle() = 0;

public:
    explicit AbstractInterface(QWidget *parent = nullptr);
    virtual Person GetPerson() const = 0;
};

#endif // ABSTRACTINTERFACE_H
