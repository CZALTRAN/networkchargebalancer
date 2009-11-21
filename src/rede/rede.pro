QT += network
QT -= gui

TARGET = rede
TEMPLATE = lib

DEFINES += REDE_LIBRARY

DESTDIR = build
MOC_DIR = build
OBJECTS_DIR = build

SOURCES += gerenciadorrede.cpp \
    lib/conexao.cpp \
    lib/ouvinte.cpp \
    gerenciadorconexao.cpp \
    peer.cpp
HEADERS += gerenciadorrede.h \
    rede_global.h \
    lib/conexao.h \
    lib/ouvinte.h \
    gerenciadorconexao.h \
    peer.h
