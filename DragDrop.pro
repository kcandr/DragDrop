#-------------------------------------------------
#
# Project created by QtCreator 2013-01-31T23:04:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DragDrop
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/blanklist.cpp \
    src/tablewidget.cpp

HEADERS  += src/mainwindow.h \
    src/blanklist.h \
    src/tablewidget.h

RESOURCES += \
    drag.qrc
