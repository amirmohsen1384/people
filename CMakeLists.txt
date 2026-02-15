cmake_minimum_required(VERSION 3.19)
project(People VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/camera
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/dialogs
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/widgets
)

find_package(Qt6 6.4 REQUIRED COMPONENTS 
    Core 
    Widgets 
    Multimedia 
    MultimediaWidgets
)

set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src)

qt_add_executable(People
    MANUAL_FINALIZATION
    ${SOURCE}/app/core.cpp
    ${SOURCE}/app/edit.cpp
    ${SOURCE}/app/file.cpp
    ${SOURCE}/app/interaction.cpp
    ${SOURCE}/data/differencedate.cpp
    ${SOURCE}/dialogs/abstractinterface.cpp
    ${SOURCE}/dialogs/personviewer.cpp
    ${SOURCE}/camera/camerasettings.cpp
    ${SOURCE}/camera/photographer.cpp
    ${SOURCE}/model/peopledelegate.cpp
    ${SOURCE}/model/peoplemodel.cpp
    ${SOURCE}/dialogs/personeditor.cpp
    ${SOURCE}/image/imageview.cpp
    ${SOURCE}/saverequest.cpp
    ${SOURCE}/widgets/personview.cpp
    ${SOURCE}/widgets/personedit.cpp
    ${SOURCE}/data/firstnamevalidator.cpp
    ${SOURCE}/data/lastnamevalidator.cpp
    ${SOURCE}/dialogs/aboutdialog.cpp
    ${SOURCE}/data/person.cpp
    ${SOURCE}/dialogs/aboutdialog.h
    ${SOURCE}/application.h
    ${SOURCE}/data/differencedate.h
    ${SOURCE}/dialogs/abstractinterface.h
    ${SOURCE}/model/peopledelegate.h
    ${SOURCE}/model/peoplemodel.h
    ${SOURCE}/camera/camerasettings.h
    ${SOURCE}/dialogs/personeditor.h
    ${SOURCE}/image/imageview.h
    ${SOURCE}/saverequest.h
    ${SOURCE}/widgets/personedit.h
    ${SOURCE}/data/firstnamevalidator.h
    ${SOURCE}/data/lastnamevalidator.h
    ${SOURCE}/data/person.h
    ${SOURCE}/widgets/personview.h
    ${SOURCE}/camera/photographer.h
    ${SOURCE}/dialogs/personviewer.h
    resources.qrc
    main.cpp
)

target_include_directories(People
    PRIVATE
        ${SOURCE}
)

target_link_libraries(People
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Multimedia
        Qt6::MultimediaWidgets
)

set_target_properties(People PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

include(GNUInstallDirs)

install(TARGETS People
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_finalize_executable(People)
