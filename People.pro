QT += core
QT += gui
CONFIG += c++2a
QT += multimedia
QT += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    src/dialogs/personviewer.cpp \
    src/camera/camerasettings.cpp \
    src/camera/photographer.cpp \
    src/application.cpp \
    src/dialogs/personeditor.cpp \
    src/image/imageview.cpp \
    src/widgets/personview.cpp \
    src/widgets/personedit.cpp \
    src/data/firstnamevalidator.cpp \
    src/data/lastnamevalidator.cpp \
    src/data/person.cpp


HEADERS += \
    include/application.h \
    include/camera/camerasettings.h \
    include/dialogs/personeditor.h \
    include/image/imageview.h \
    include/widgets/personedit.h \
    include/data/firstnamevalidator.h \
    include/data/lastnamevalidator.h \
    include/data/person.h \
    include/widgets/personview.h \
    include/camera/photographer.h \
    include/dialogs/personviewer.h

FORMS += \
    gui/application.ui \
    gui/camera/camerasettings.ui \
    gui/dialogs/personeditor.ui \
    gui/widgets/personedit.ui \
    gui/widgets/personview.ui \
    gui/camera/photographer.ui \
    gui/dialogs/personviewer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
