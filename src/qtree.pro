#-------------------------------------------------
#
# Project created by QtCreator 2019-07-22T00:49:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = $$PWD/../bin

TARGET = qtree
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    alistview.cpp

HEADERS  += widget.h \
    alistview.h

FORMS    += widget.ui \
    alistview.ui
