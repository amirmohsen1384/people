#include "include/application.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Application window;
    window.show();

    return app.exec();
}
