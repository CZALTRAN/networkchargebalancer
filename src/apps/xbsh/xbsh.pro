# -------------------------------------------------
# Project created by QtCreator 2009-12-09T15:16:37
# -------------------------------------------------
QT += dbus \
    thread
QT -= gui
TARGET = xbsh
CONFIG += console
CONFIG -= app_bundle
OBJECTS_DIR = build
DESTDIR = build
MOC_DIR = build
TEMPLATE = app
SOURCES += main.cpp \
    ../gpinterface.cpp \
    xbsh.cpp \
    standardinput.cpp \
    gerenciadorlancamento.cpp \
    processonativopai.cpp \
    ps/ps.cpp \
    kill/kill.cpp
HEADERS += ../gpinterface.h \
    xbsh.h \
    standardinput.h \
    gerenciadorlancamento.h \
    processonativopai.h \
    ps/ps.h \
    kill/kill.h
