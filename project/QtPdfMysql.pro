#-------------------------------------------------
#
# Project created by QtCreator 2015-07-17T02:42:32
#
#-------------------------------------------------

QT       += sql core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTpdf
TEMPLATE = app


QT += core

QT       += printsupport

SOURCES += src/main.cpp\
        src/mainwindow.cpp

HEADERS  += include/mainwindow.h

FORMS    += mainwindow.ui
