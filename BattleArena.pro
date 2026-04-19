QT += core gui widgets

CONFIG += c++17

TARGET = BattleArena
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    character.cpp \
    battlefieldwidget.cpp

HEADERS += \
    mainwindow.h \
    character.h \
    battlefieldwidget.h
