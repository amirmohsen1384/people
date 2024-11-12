#include "include/data/person.h"
#include "include/application.h"
#include <QApplication>
#include <QFile>
#include "include/dialogs/personeditdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PersonEditDialog dialog;
    dialog.exec();

    return app.exec();
}
