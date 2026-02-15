#ifndef SAVEREQUEST_H
#define SAVEREQUEST_H

#include <QObject>
#include <QMessageBox>

class SaveRequest : public QObject
{
    Q_OBJECT
    bool required;

public:
    enum Result {
        Unknown = 0x00,
        Rejected = 0x02,
        SaveFirst = 0x01,
        NotRequired = 0x04,
        DiscardFirst = 0x08
    };
    Q_ENUM(Result)

    explicit SaveRequest(bool initial = false, QObject *parent = nullptr);
    bool IsRequired() const;

public slots:
    void SetRequired(bool state);
    SaveRequest::Result Request(QWidget *parent = nullptr);

signals:
    void StateChanged(bool required);
};

#endif // SAVEREQUEST_H
