QT += core
QT += gui
CONFIG += c++2a
QT += multimedia
QT += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    src/app/core.cpp \
    src/app/edit.cpp \
    src/app/file.cpp \
    src/data/differencedate.cpp \
    src/dialogs/personviewer.cpp \
    src/camera/camerasettings.cpp \
    src/camera/photographer.cpp \
    src/model/peopledelegate.cpp \
    src/model/peoplemodel.cpp \
    src/dialogs/personeditor.cpp \
    src/image/imageview.cpp \
    src/saverequest.cpp \
    src/widgets/personview.cpp \
    src/widgets/personedit.cpp \
    src/data/firstnamevalidator.cpp \
    src/data/lastnamevalidator.cpp \
    src/data/person.cpp


HEADERS += \
    include/application.h \
    include/data/differencedate.h \
    include/model/peopledelegate.h \
    include/model/peoplemodel.h \
    include/camera/camerasettings.h \
    include/dialogs/personeditor.h \
    include/image/imageview.h \
    include/saverequest.h \
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
