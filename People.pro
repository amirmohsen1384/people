QT += core
QT += gui
CONFIG += c++2a
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    application.cpp \
    src/data/person.cpp

HEADERS += \
    application.h \
    include/data/person.h

FORMS += \
    application.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
