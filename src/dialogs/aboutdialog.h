#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT
    Ui::AboutDialog *ui = nullptr;
private slots:
    void OpenIssueTracker();
    void OpenGitHubRepository();

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

private:

};

#endif // ABOUTDIALOG_H
