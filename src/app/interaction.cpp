#include "include/application.h"
#include "ui_application.h"

void Application::ConnectActions() {
    connect(ui->newAction, &QAction::triggered, this, &Application::New);
    connect(ui->openAction, &QAction::triggered, this, &Application::Open);
    connect(ui->saveAsAction, &QAction::triggered, this, &Application::SaveAs);
    connect(ui->saveAction, &QAction::triggered, this, QOverload<>::of(&Application::Save));
    connect(ui->closeAction, &QAction::triggered, this, &Application::Close);

    connect(ui->addAction, &QAction::triggered, this, &Application::Add);
    connect(ui->editAction, &QAction::triggered, this, QOverload<>::of(&Application::Edit));
    connect(ui->deleteAction, &QAction::triggered, this, QOverload<>::of(&Application::Delete));
    connect(ui->clearAction, &QAction::triggered, this, &Application::Clear);
    connect(ui->viewAction, &QAction::triggered, this, QOverload<>::of(&Application::View));

    connect(ui->aboutAction, &QAction::triggered, this, &Application::About);
    connect(ui->AboutQtAction, &QAction::triggered, this, [&]() { QApplication::aboutQt(); });
}

void Application::ConnectList() {
    connect(&model, &PeopleModel::ItemCountChanged, this, [&](int count) {
        ui->clearAction->setEnabled(count != 0);
        if(count == 0) {
            ui->deleteAction->setEnabled(false);
            ui->editAction->setEnabled(false);
            ui->viewAction->setEnabled(false);
        }
    });
    connect(ui->container->selectionModel(), &QItemSelectionModel::selectionChanged, [&](const QItemSelection &selected, const QItemSelection &deselected) {
        Q_UNUSED(deselected);
        Q_UNUSED(selected);
        const QModelIndexList &indices = ui->container->selectionModel()->selectedIndexes();
        ui->deleteAction->setDisabled(indices.isEmpty());
        ui->editAction->setEnabled(indices.size() == 1);
        ui->viewAction->setEnabled(indices.size() == 1);
    });
    connect(ui->container, &QListView::activated, this, QOverload<const QModelIndex &>::of(&Application::View));
}
