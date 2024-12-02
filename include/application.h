#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include "include/model/peoplemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Application;
}
QT_END_NAMESPACE

class Application : public QMainWindow
{
    Q_OBJECT
    PeopleModel model;
    Ui::Application *ui;

protected slots:
    bool Load(const QString &filename);
    bool Save(const QString &filename);

    void Add();
    void Save();
    void Clear();
    void SaveAs();
    void Edit(const QModelIndex &index);
    void Delete(const QModelIndexList &indices);

public:
    Application(QWidget *parent = nullptr);
    ~Application();
};
#endif // APPLICATION_H
