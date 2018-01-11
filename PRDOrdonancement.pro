#-------------------------------------------------
#
# Project created by QtCreator 2018-01-10T15:18:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PRDOrdonancement
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    generateinstance.cpp \
    resolveinstance.cpp \
    workermip1.cpp

HEADERS  += mainwindow.h \
    generateinstance.h \
    resolveinstance.h \
    workermip1.h

FORMS    += mainwindow.ui \
    generateinstance.ui \
    resolveinstance.ui
