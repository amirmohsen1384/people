#include "include/model/peopledelegate.h"
#include "include/dialogs/aboutdialog.h"
#include "include/application.h"
#include "ui_application.h"

Application::Application(QWidget *parent) : QMainWindow(parent), ui(new Ui::Application) {
    ui->setupUi(this);
    ui->container->setModel(&model);
    ui->container->setItemDelegate(new PeopleDelegate);
    ConnectActions();
    ConnectList();
}

Application::~Application()
{
    delete ui;
}

void Application::About() {
    AboutDialog dialog(this);
    dialog.exec();
}
