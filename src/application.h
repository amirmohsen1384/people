#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include "saverequest.h"
#include "model/peoplemodel.h"

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
private slots:
    void ConnectList();
    void ConnectActions();

protected:
    bool Load(const QString &filename);
    bool Save(const QString &filename);
    void Edit(const QModelIndex &index);
    void View(const QModelIndex &index);
    void Delete(QModelIndexList &indices);
    void closeEvent(QCloseEvent *event) override;

protected slots:
    void New();
    void Add();
    void Open();
    bool Save();
    void Edit();
    void View();
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
