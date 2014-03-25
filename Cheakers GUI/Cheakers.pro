#-------------------------------------------------
#
# Project created by QtCreator 2014-03-20T20:06:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cheakers
TEMPLATE = app

CONFIG += app_bundle
CONFIG += console
CONFIG += c++11

SOURCES += main.cpp\
        mainviewcontroller.cpp \
    ../board.cpp \
    ../game.cpp \
    ../minimax.cpp \
    ../node.cpp

HEADERS  += mainviewcontroller.h \
    ../board.h \
    ../game.h \
    ../struct.h \
    ../minimax.h \
    ../node.h

FORMS    += mainviewcontroller.ui

OTHER_FILES += \
    ../Makefile \
    ../README.md

RESOURCES += \
    resourses.qrc
