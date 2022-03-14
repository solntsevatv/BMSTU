QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    baseobject.cpp \
    camera.cpp \
    canvaslabel.cpp \
    directionallight.cpp \
    main.cpp \
    mainwindow.cpp \
    matrix.cpp \
    mesh.cpp \
    meshloader.cpp \
    scenemanager.cpp \
    triangle.cpp \
    vector3.cpp


HEADERS += \
    baseobject.h \
    camera.h \
    canvaslabel.h \
    directionallight.h \
    mainwindow.h \
    matrix.h \
    mesh.h \
    meshloader.h \
    scenemanager.h \
    triangle.h \
    vector3.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

INCLUDEPATH = "D:\SoftwareStorage\Python\include" "D:\SoftwareStorage\Python\Lib" "D:\SoftwareStorage\Python\libs"
LIBS += -L"D:\SoftwareStorage\Python\libs" -L"D:\SoftwareStorage\Python\Lib" -l"python39"
