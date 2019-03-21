#-------------------------------------------------
#
# Project created by QtCreator 2018-08-13T14:20:00
#
#-------------------------------------------------

QT       += core gui

RC_ICONS = app_ico.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RTT
TEMPLATE = app

# 添加子文件夹路径，否则，include子文件夹下的h文件时，编译时报错，找不到h文件
INCLUDEPATH += rtt \
            comfunc

SOURCES += main.cpp\
        mainwindow.cpp \
    comfunc/comfunc_qt.cpp \
    comfunc/comfunc.c \
    comfunc/gfifo.cpp \
    seggerop.cpp \
    comboboxex.cpp


HEADERS  += mainwindow.h \
    comfunc/comfunc.h \
    comfunc/comfunc_qt.h \
    comfunc/gfifo.h \
    seggerop.h \
    comboboxex.h


FORMS    += mainwindow.ui




