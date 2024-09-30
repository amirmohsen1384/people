#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Application;
}
QT_END_NAMESPACE

class Application : public QMainWindow
{
    Q_OBJECT

public:
    Application(QWidget *parent = nullptr);
    ~Application();

private:
    Ui::Application *ui;
};
#endif // APPLICATION_H
