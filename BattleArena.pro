QT += core gui widgets

CONFIG += c++17

TARGET = BattleArena
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    character.cpp \
    battlefieldwidget.cpp \
    game.cpp \
    inputhandler.cpp \
    ai.cpp \
    scoremanager.cpp \
    animationmanager.cpp \
    savemanager.cpp

HEADERS += \
    mainwindow.h \
    character.h \
    battlefieldwidget.h \
    game.h \
    inputhandler.h \
    ai.h \
    scoremanager.h \
    animationmanager.h \
    savemanager.h
