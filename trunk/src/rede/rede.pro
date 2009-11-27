QT += network
QT -= gui

TEMPLATE = app
TARGET = rede
DEFINES += REDE_LIBRARY
DESTDIR = build
MOC_DIR = build
OBJECTS_DIR = build

HEADERS += construtordepacotes.h \
           gerenciadorconexao.h \
           gerenciadorrede.h \
           parserdepacotes.h \
           peer.h \
           ping.h \
           rede_global.h \
           redeconfig.h \
           structpacotes.h \
           lib/conexao.h \
           lib/getifaddrfromadapter.h \
           lib/ouvinte.h

SOURCES += construtordepacotes.cpp \
           gerenciadorconexao.cpp \
           gerenciadorrede.cpp \
           main.cpp \
           parserdepacotes.cpp \
           peer.cpp \
           ping.cpp \
           redeconfig.cpp \
           lib/conexao.cpp \
           lib/getifaddrfromadapter.cpp \
           lib/ouvinte.cpp
