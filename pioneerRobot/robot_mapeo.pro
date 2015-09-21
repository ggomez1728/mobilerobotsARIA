#-------------------------------------------------
#
# Project created by QtCreator 2015-07-14T22:44:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = robot_mapeo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    grilla.cpp \
    celda.cpp \
    pioneerrobot.cpp \
    crobotmap.cpp \
    csonar.cpp

HEADERS  += mainwindow.h \
    grilla.h \
    celda.h \
    pioneerrobot.h \
    crobotmap.h \
    Types.h \
    csonar.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/Aria/include

LIBS += -L/usr/local/Aria/lib -lAria

LIBS += -lrt -ldl -lpthread

HEADERS += \
    lib_robotica_ucla.h

RESOURCES += \
    myResources.qrc
