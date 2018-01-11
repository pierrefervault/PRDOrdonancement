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
    workermip1.cpp \
    plne.cpp

HEADERS  += mainwindow.h \
    generateinstance.h \
    resolveinstance.h \
    workermip1.h \
    plne.h

FORMS    += mainwindow.ui \
    generateinstance.ui \
    resolveinstance.ui

#INCLUDEPATH += /home/pierre/build-PRDOrdonancement-Desktop_Qt_5_7_0_GCC_64bit-Debug/cplex_216/cplex/include
#INCLUDEPATH += /home/pierre/build-PRDOrdonancement-Desktop_Qt_5_7_0_GCC_64bit-Debug/cplex_216/concert/include
 
#DEFINES += IL_STD
 
#LIBS += -L/home/pierre/build-PRDOrdonancement-Desktop_Qt_5_7_0_GCC_64bit-Debug/cplex_216/cplex/lib/x86-64_linux/static_pic -lilocplex -lconcert -lcplex -lm -lpthread
#LIBS += -L/home/pierre/build-PRDOrdonancement-Desktop_Qt_5_7_0_GCC_64bit-Debug/cplex_216/concert/lib/x86-64_linux/static_pic -lconcert
