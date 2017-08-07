#-------------------------------------------------
#
# Project created by QtCreator 2017-08-07T17:31:52
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DemoPlot
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = build_/release
            TARGET  = DemoPlot
        } else {
            target_path = build_/debug
            TARGET  = DemoPlot
        }
        DESTDIR = bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        UI_DIR  = $$target_path/ui
        OBJECTS_DIR = $$target_path/obj
}

DEPENDPATH += bin

include($$PWD/qcustomplot/qcustomplot.pri)

INCLUDEPATH +=$$PWD/qcustomplot

SOURCES += main.cpp\
        widget.cpp \
    senddatathread.cpp

HEADERS  += widget.h \
    senddatathread.h

FORMS    += widget.ui
