# -------------------------------------------------
# Project created by QtCreator 2009-11-29T22:39:12
# -------------------------------------------------
QT -= gui
TARGET = gp
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
DESTDIR = build
MOC_DIR = build
OBJECTS_DIR = build
SOURCES += main.cpp \
    gerenciadorprocessos.cpp \
    launcher.cpp \
    balanceadorcarga.cpp \
    gpconfig.cpp \
    processo.cpp \
    parserdepacotes.cpp \
    construtordepacotes.cpp \
    gppeer.cpp \
    processolocalouimportado.cpp \
    processoexportado.cpp
HEADERS += gerenciadorprocessos.h \
    launcher.h \
    balanceadorcarga.h \
    gpconfig.h \
    processo.h \
    structpacotes.h \
    parserdepacotes.h \
    construtordepacotes.h \
    gppeer.h \
    processolocalouimportado.h \
    processoexportado.h
