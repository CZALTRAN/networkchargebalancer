
QT += network
QT -= gui

TARGET = rede
TEMPLATE = lib

DEFINES += REDE_LIBRARY

DESTDIR = build
MOC_DIR = build
OBJECTS_DIR = build

SOURCES += rede.cpp \
    lib/conexao.cpp
HEADERS += rede.h \
    rede_global.h \
    lib/conexao.h
