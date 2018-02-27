#-------------------------------------------------
#
# Project created by QtCreator 2017-12-23T19:34:49
#
#-------------------------------------------------

QT += core gui widgets xml

DESTDIR += $$PWD/../bin
CONFIG += c++11

TARGET = ShoeManagerCore
TEMPLATE = lib

msvc:QMAKE_CXXFLAGS += -execution-charset:utf-8
msvc:QMAKE_CXXFLAGS += -source-charset:utf-8

DEFINES += SHOEMANAGERCORE_LIBRARY

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
    QUtilsFramelessWidget.cpp \
    QUtilsFramelessHelper.cpp \
    QUtilsFramelessDialog.cpp \
    IconFont.cpp \
    zlistwidget.cpp \
    navlistview.cpp \
    QUtilsFramLessMessageBox.cpp \
    QUtilsFramelessForm.cpp \
    switchbutton.cpp \
    QUtilsLayoutLine.cpp \
    QUtilsBetterTableView.cpp \
    QUtilsBusyIndicator.cpp \
    QUtilsButtonsDelegate.cpp \
    ShoeManagerNamespace.cpp \
    QUtilsCoreApplication.cpp \
    logger.cpp

HEADERS += \
        shoemanagercore_global.h \ 
    QUtilsFramelessWidget.hpp \
    QUtilsFramelessHelper.hpp \
    QUtilsFramelessDialog.hpp \
    IconFont.hpp \
    zlistwidget.h \
    navlistview.h \
    QUtilsFramLessMessageBox.hpp \
    QUtilsFramelessForm.hpp \
    switchbutton.h \
    QUtilsLayoutLine.hpp \
    QUtilsBetterTableView.hpp \
    QUtilsBusyIndicator.hpp \
    QUtilsButtonsDelegate.hpp \
    ShoeManagerNamespace.h \
    QUtilsCoreApplication.hpp \
    logger.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    ShoeManagerCore.pri

RESOURCES += \
    iconfont.qrc
