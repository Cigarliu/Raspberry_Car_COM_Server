TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        lib/controller.cpp \
        lib/tcpserver.cpp \
        lib/udpserver.cpp \
        main.cpp

HEADERS += \
    lib/controller.h \
    lib/tcpserver.h \
    lib/udpserver.h

LIBS += -lpthread
