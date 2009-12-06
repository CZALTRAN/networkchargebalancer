QT += console \
    dbus
QT -= gui
TARGET = dbus
TEMPLATE = app
OBJECTS_DIR = build
MOC_DIR = build
DESTDIR = build
SOURCES += main.cpp \
    gerenciadordbus.cpp \
    dbusconfig.cpp \
    gpadaptor.cpp \
    redeadaptor.cpp
HEADERS += gerenciadordbus.h \
    dbusconfig.h \
    gpadaptor.h \
    redeadaptor.h
