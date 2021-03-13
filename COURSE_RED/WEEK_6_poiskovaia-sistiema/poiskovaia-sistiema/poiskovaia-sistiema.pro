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
    parse.cpp \
    search_server.cpp

HEADERS += \
    iterator_range.h \
    parse.h \
    search_server.h \
    test_runner.h \
    profile.h \
    chronometer.h \
    synchronized.h

