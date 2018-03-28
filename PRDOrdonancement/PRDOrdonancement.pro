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
    generationinstance.cpp \
    resolutioninstance.cpp \
    fenetreprincipale.cpp \
    workerfichier.cpp \
    workerdossier.cpp \
    workerinstance.cpp \
    instance.cpp \
    comparaisonsolution.cpp \
    workercomparaison.cpp \
    calculcomparaison.cpp \
    heuristique.cpp\
    resultat.cpp

HEADERS  += \
    methodeexacte.h \
    generationinstance.h \
    resolutioninstance.h \
    fenetreprincipale.h \
    workerfichier.h \
    workerdossier.h \
    workerinstance.h \
    instance.h \
    comparaisonsolution.h \
    workercomparaison.h \
    calculcomparaison.h \
    heuristique.h \
    resultat.h

FORMS    += \
    generationinstance.ui \
    resolutioninstance.ui \
    fenetreprincipale.ui \
    comparaisonsolution.ui

INCLUDEPATH += /home/pierre/cplex_216/cplex/include
INCLUDEPATH += /home/pierre/cplex_216/concert/include

DEFINES += IL_STD
 
LIBS += -L/home/pierre/cplex_216/cplex/lib/x86-64_linux/static_pic -lilocplex -lconcert -lcplex -lm -lpthread
LIBS += -L/home/pierre/cplex_216/concert/lib/x86-64_linux/static_pic -lconcert

CONFIG += qwt
INCLUDEPATH += /usr/local/qwt-6.1.3/include
LIBS += -L /usr/local/qwt-6.1.3/lib -lqwt

include(/usr/local/qwt-6.1.3/features/qwt.prf)

RESOURCES += \
    ressources.qrc
