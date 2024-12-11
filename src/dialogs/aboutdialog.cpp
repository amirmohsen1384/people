#include "include/dialogs/aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QDesktopServices>

void AboutDialog::OpenIssueTracker() {
    QDesktopServices::openUrl(QUrl("https://github.com/amirmohsen1384/people/issues"));
}
void AboutDialog::OpenGitHubRepository() {
    QDesktopServices::openUrl(QUrl("https://github.com/amirmohsen1384/people"));
}

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog) {
    ui->setupUi(this);
    this->setFixedSize(this->size());
    connect(ui->issueButton, &QCommandLinkButton::clicked, this, &AboutDialog::OpenIssueTracker);
    connect(ui->repositorybutton, &QCommandLinkButton::clicked, this, &AboutDialog::OpenGitHubRepository);
}
AboutDialog::~AboutDialog() {
    delete ui;
}
