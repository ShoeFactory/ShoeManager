#-------------------------------------------------
#
# Project created by QtCreator 2017-12-23T19:59:31
#
#-------------------------------------------------

QT       += network

QT       -= gui

DESTDIR += $$PWD/../bin
LIBS += -L$$PWD/../bin
include($$PWD/../ShoeManagerCore/ShoeManagerCore.pri)

CONFIG += c++11

msvc:QMAKE_CXXFLAGS += -execution-charset:utf-8

TARGET = ShoeManagerNetwork
TEMPLATE = lib

DEFINES += SHOEMANAGERNETWORK_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ShoeManagerNetworkAccessManager.cpp \
    ShoeManagerNetworkConfig.cpp \
    ShoeManagerNetwork.cpp \
    ShoeManagerNetworkResult.cpp \
    ShoeManagerTcpClient.cpp \
    ShoeManagerTcpServer.cpp \
    ShoeManagerTcpSocket.cpp \
    ShoeManagerTcpPacket.cpp \
    ShoeManagerTcpServerPrivate.cpp

HEADERS += \
        shoemanagernetwork_global.h \ 
    ShoeManagerNetworkAccessManager.hpp \
    ShoeManagerNetworkConfig.hpp \
    ShoeManagerNetwork.hpp \
    ShoeManagerNetworkResult.hpp \
    ShoeManagerTcpClient.hpp \
    ShoeManagerTcpServer.hpp \
    ShoeManagerTcpSocket.hpp \
    ShoeManagerTcpPacket.hpp \
    ShoeManagerTcpServerPrivate.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    ShoeManagerNetwork.pri
