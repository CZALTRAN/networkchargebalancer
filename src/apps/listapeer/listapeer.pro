QT += gui \
    dbus
TEMPLATE = app
TARGET = listapeer
MOC_DIR = build
DESTDIR = build
OBJECTS_DIR = build
INCLUDEPATH += ../
SOURCES += main.cpp \
    listapeerwidget.cpp \
    ../redeinterface.cpp
HEADERS += listapeerwidget.h \
    ../redeinterface.h
