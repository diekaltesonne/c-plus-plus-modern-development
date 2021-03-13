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
    descriptions.cpp \
    json.cpp \
    requests.cpp \
    sphere.cpp \
    transport_catalog.cpp \
    transport_router.cpp \
    utils.cpp

HEADERS += \
    descriptions.h \
    graph.h \
    json.h \
    requests.h \
    router.h \
    sphere.h \
    transport_catalog.h \
    transport_router.h \
    utils.h

