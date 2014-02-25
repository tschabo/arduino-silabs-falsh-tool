#-------------------------------------------------
#
# Project created by QtCreator 2012-08-31T19:52:49
#
#-------------------------------------------------

include(external/qextserialport-1.2beta2/src/qextserialport.pri)

QT       += core

TARGET = SiArduFlash
TEMPLATE = app


SOURCES += main.cpp \
    cserialcommunication.cpp \
    cprogrammer.cpp \
    cabstractoutputhandler.cpp \
    cstdoutoutputhandler.cpp

HEADERS  += common.h \
    cserialcommunication.h \
    cprogrammer.h \
    cabstractoutputhandler.h \
    cstdoutoutputhandler.h


