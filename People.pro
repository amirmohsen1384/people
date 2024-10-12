QT += core
QT += gui
CONFIG += c++2a
QT += multimedia
QT += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    src/camera/photographer.cpp \
    src/application.cpp \
    src/widgets/personedit.cpp \
    src/data/firstnamevalidator.cpp \
    src/data/lastnamevalidator.cpp \
    src/data/person.cpp

HEADERS += \
    include/application.h \
    include/widgets/personedit.h \
    include/data/firstnamevalidator.h \
    include/data/lastnamevalidator.h \
    include/data/person.h \
    include/camera/photographer.h

FORMS += \
    gui/application.ui \
    gui/widgets/personedit.ui \
    gui/camera/photographer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
