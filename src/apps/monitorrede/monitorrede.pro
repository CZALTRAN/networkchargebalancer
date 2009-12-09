QT += gui \
    dbus
TEMPLATE = app
TARGET = monitor_rede_xboga
DESTDIR = build
OBJECTS_DIR = build
MOC_DIR = build
INCLUDEPATH += ../ \
    ../listapeer
HEADERS += ../listapeer/listapeerwidget.h \
    ../redeinterface.h \
    monitorrede.h
SOURCES += ../listapeer/listapeerwidget.cpp \
    ../redeinterface.cpp \
    main.cpp \
    monitorrede.cpp
FORMS += monitor_rede.ui
