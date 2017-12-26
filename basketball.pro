#-------------------------------------------------
#
# Project created by QtCreator 2017-06-20T15:37:08
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = basketball
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fanlogin.cpp \
    teamlogin.cpp \
    manlogin.cpp \
    fanoper.cpp \
    teamoper.cpp \
    manoper.cpp \
    fanregister.cpp \
    teamregister.cpp \
    viewplayer.cpp \
    viewteam.cpp \
    fanviewteam.cpp \
    fanviewplayer.cpp \
    buy.cpp

HEADERS  += mainwindow.h \
    fanlogin.h \
    teamlogin.h \
    manlogin.h \
    fanoper.h \
    teamoper.h \
    manoper.h \
    fanregister.h \
    teamregister.h \
    viewplayer.h \
    viewteam.h \
    fanviewteam.h \
    fanviewplayer.h \
    buy.h

FORMS    += mainwindow.ui \
    fanlogin.ui \
    teamlogin.ui \
    manlogin.ui \
    fanoper.ui \
    teamoper.ui \
    manoper.ui \
    fanregister.ui \
    teamregister.ui \
    viewplayer.ui \
    viewteam.ui \
    fanviewteam.ui \
    fanviewplayer.ui \
    buy.ui
