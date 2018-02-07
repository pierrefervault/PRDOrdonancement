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
    methodeexacte.cpp \
    heuristique.cpp \
    generationinstance.cpp \
    resolutioninstance.cpp \
    fenetreprincipale.cpp \
    workerfichier.cpp \
    workerdossier.cpp \
    workerinstance.cpp \
    instance.cpp

HEADERS  += \
    methodeexacte.h \
    heuristique.h \
    generationinstance.h \
    resolutioninstance.h \
    fenetreprincipale.h \
    workerfichier.h \
    workerdossier.h \
    workerinstance.h \
    instance.h
    

FORMS    += \
    generationinstance.ui \
    resolutioninstance.ui \
    fenetreprincipale.ui

INCLUDEPATH += /home/pierre/build-PRDOrdonancement-Desktop_Qt_5_7_0_GCC_64bit-Debug/PRDOrdonancement/cplex_216/cplex/include
INCLUDEPATH += /home/pierre/build-PRDOrdonancement-Desktop_Qt_5_7_0_GCC_64bit-Debug/PRDOrdonancement/cplex_216/concert/include
 
DEFINES += IL_STD
 
LIBS += -L/home/pierre/build-PRDOrdonancement-Desktop_Qt_5_7_0_GCC_64bit-Debug/PRDOrdonancement/cplex_216/cplex/lib/x86-64_linux/static_pic -lilocplex -lconcert -lcplex -lm -lpthread
LIBS += -L/home/pierre/build-PRDOrdonancement-Desktop_Qt_5_7_0_GCC_64bit-Debug/PRDOrdonancement/cplex_216/concert/lib/x86-64_linux/static_pic -lconcert
