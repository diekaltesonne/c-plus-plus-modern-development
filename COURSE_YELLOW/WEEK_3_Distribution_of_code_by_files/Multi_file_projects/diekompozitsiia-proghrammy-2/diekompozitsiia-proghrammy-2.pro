TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    query.cpp \
    responses.cpp \
    bus_manager.cpp

HEADERS += \
    query.h \
    responses.h \
    bus_manager.h

