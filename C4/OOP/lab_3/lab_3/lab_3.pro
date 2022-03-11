QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basecommand.cpp \
    basemanager.cpp \
    baseobject.cpp \
    baseobjectvisitor.cpp \
    basestate.cpp \
    basetransform.cpp \
    cameracommands.cpp \
    commandcontroller.cpp \
    editorcommands.cpp \
    facade.cpp \
    main.cpp \
    mainmanager.cpp \
    mainwindow.cpp \
    memento.cpp \
    objectcommands.cpp \
    objectid.cpp \
    objectstate.cpp \
    rendercommands.cpp \
    rendermanager.cpp \
    scene.cpp \
    scenecaretaker.cpp \
    scenecommands.cpp \
    scenestate.cpp \
    selectioncommands.cpp \
    statecommands.cpp \
    transformcommands.cpp \
    transfrom3d.cpp

HEADERS += \
    basecommand.h \
    basemanager.h \
    baseobject.h \
    baseobjectvisitor.h \
    basestate.h \
    basetransform.h \
    cameracommands.h \
    commandcontroller.h \
    editorcommands.h \
    facade.h \
    mainmanager.h \
    mainwindow.h \
    memento.h \
    objectcommands.h \
    objectid.h \
    objectstate.h \
    rendercommands.h \
    rendermanager.h \
    scene.h \
    scenecaretaker.h \
    scenecommands.h \
    scenestate.h \
    selectioncommands.h \
    statecommands.h \
    transformcommands.h \
    transfrom3d.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
