TEMPLATE = app
CONFIG += thread
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXX = g++-7
QMAKE_CC = gcc-7
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS+= -std=gnu++17

SOURCES += main.cpp \
    Textures.cpp \
    common.cpp

HEADERS += \
    Textures.h \
    Common.h \
    test_runner.h

