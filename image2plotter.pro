QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += svgwidgets openglwidgets

CONFIG += c++11

INCLUDEPATH += ./include ./forms ./src

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp\
    src/drawingLayer.cpp\
    src/drawingViewer.cpp

HEADERS += \
    include/mainwindow.h\
    include/drawingLayer.hpp\
    include/drawingViewer.hpp

FORMS += \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
