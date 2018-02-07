QT += core testlib
QT -= gui

CONFIG += c++11

TARGET = Test
CONFIG += console
CONFIG -= app_bundle
CONFIG += testcase

TEMPLATE = app

SOURCES += \
    classtest.cpp \
    main.cpp

HEADERS += \
    classtest.h

INCLUDEPATH += $$PWD/../PRDOrdonancement

SOURCES += \
    $$PWD/../PRDOrdonancement/methodeexacte.cpp \
    $$PWD/../PRDOrdonancement/heuristique.cpp \
    $$PWD/../PRDOrdonancement/instance.cpp

HEADERS  += \
    $$PWD/../PRDOrdonancement/methodeexacte.h \
    $$PWD/../PRDOrdonancement/heuristique.h \
    $$PWD/../PRDOrdonancement/instance.h

INCLUDEPATH += /home/pierre/build-PRDOrdonancement-Desktop_Qt_5_7_0_GCC_64bit-Debug/PRDOrdonancement/cplex_216/cplex/include
INCLUDEPATH += /home/pierre/build-PRDOrdonancement-Desktop_Qt_5_7_0_GCC_64bit-Debug/PRDOrdonancement/cplex_216/concert/include

DEFINES += IL_STD

LIBS += -L/home/pierre/build-PRDOrdonancement-Desktop_Qt_5_7_0_GCC_64bit-Debug/PRDOrdonancement/cplex_216/cplex/lib/x86-64_linux/static_pic -lilocplex -lconcert -lcplex -lm -lpthread
LIBS += -L/home/pierre/build-PRDOrdonancement-Desktop_Qt_5_7_0_GCC_64bit-Debug/PRDOrdonancement/cplex_216/concert/lib/x86-64_linux/static_pic -lconcert
