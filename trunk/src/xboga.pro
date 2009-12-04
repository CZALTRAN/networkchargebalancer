QT += console \
    network
QT -= gui
TARGET = xboga
TEMPLATE = app
DESTDIR = build
MOC_DIR = build
OBJECTS_DIR = build
SOURCES += main.cpp \
    xbogainittializer.cpp \
    rede/redeconfig.cpp \
    rede/gerenciadorrede.cpp \
    rede/gerenciadorconexao.cpp \
    rede/construtordepacotes.cpp \
    rede/ping.cpp \
    rede/peer.cpp \
    rede/parserdepacotes.cpp \
    rede/lib/ouvinte.cpp \
    rede/lib/getifaddrfromadapter.cpp \
    rede/lib/conexao.cpp \
    gerenciador_processos/launcher.cpp \
    gerenciador_processos/gerenciadorprocessos.cpp \
    gerenciador_processos/balanceadorcarga.cpp
HEADERS += xbogainittializer.h \
    rede/structpacotes.h \
    rede/redeconfig.h \
    rede/rede_global.h \
    rede/gerenciadorrede.h \
    rede/gerenciadorconexao.h \
    rede/construtordepacotes.h \
    rede/ping.h \
    rede/peer.h \
    rede/parserdepacotes.h \
    rede/lib/ouvinte.h \
    rede/lib/getifaddrfromadapter.h \
    rede/lib/conexao.h \
    gerenciador_processos/launcher.h \
    gerenciador_processos/gerenciadorprocessos.h \
    gerenciador_processos/balanceadorcarga.h
