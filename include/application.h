#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include "include/saverequest.h"
#include "include/model/peoplemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Application;
}
QT_END_NAMESPACE

class Application : public QMainWindow
{
    Q_OBJECT
    SaveRequest save;
    PeopleModel model;
    Ui::Application *ui;

protected:
    bool Load(const QString &filename);
    bool Save(const QString &filename);
    void Edit(const QModelIndex &index);
    void Delete(QModelIndexList &indices);

protected slots:
    void New();
    void Add();
    void Open();
    bool Save();
    void Edit();
    void Close();
    void Clear();
    void About();
    void Delete();
    bool SaveAs();

public:
    Application(QWidget *parent = nullptr);
    ~Application();
};
#endif // APPLICATION_H
