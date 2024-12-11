#include "include/model/peopledelegate.h"
#include "include/dialogs/aboutdialog.h"
#include "include/application.h"
#include "ui_application.h"

Application::Application(QWidget *parent) : QMainWindow(parent), ui(new Ui::Application) {
    ui->setupUi(this);
    ui->container->setModel(&model);
    ui->container->setItemDelegate(new PeopleDelegate);
    connect(ui->newAction, &QAction::triggered, this, &Application::New);
    connect(ui->openAction, &QAction::triggered, this, &Application::Open);
    connect(ui->saveAsAction, &QAction::triggered, this, &Application::SaveAs);
    connect(ui->closeAction, &QAction::triggered, this, &Application::Close);
    connect(ui->addAction, &QAction::triggered, this, &Application::Add);
    connect(ui->clearAction, &QAction::triggered, this, &Application::Clear);
    connect(ui->closeAction, &QAction::triggered, this, &Application::Close);
    connect(ui->aboutAction, &QAction::triggered, this, &Application::About);
    connect(ui->saveAction, &QAction::triggered, this, QOverload<>::of(&Application::Save));
    connect(ui->saveAction, &QAction::triggered, this, QOverload<>::of(&Application::Edit));
    connect(ui->saveAction, &QAction::triggered, this, QOverload<>::of(&Application::Delete));
    connect(ui->AboutQtAction, &QAction::triggered, this, [&]() { QApplication::aboutQt(); });
}
Application::~Application()
{
    delete ui;
}

void Application::About() {
    AboutDialog dialog(this);
    dialog.exec();
}
