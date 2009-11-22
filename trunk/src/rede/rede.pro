QT += network
QT -= gui
TARGET = rede
TEMPLATE = app
DEFINES += REDE_LIBRARY
DESTDIR = build
MOC_DIR = build
OBJECTS_DIR = build
SOURCES += gerenciadorrede.cpp \
    lib/conexao.cpp \
    lib/ouvinte.cpp \
    gerenciadorconexao.cpp \
    peer.cpp \
    redeconfig.cpp \
    main.cpp \
    construtordepacotes.cpp \
    parserdepacotes.cpp \
    lib/getifaddrfromadapter.cpp
HEADERS += gerenciadorrede.h \
    rede_global.h \
    lib/conexao.h \
    lib/ouvinte.h \
    gerenciadorconexao.h \
    peer.h \
    redeconfig.h \
    construtordepacotes.h \
    parserdepacotes.h \
    structpacotes.h \
    lib/getifaddrfromadapter.h
