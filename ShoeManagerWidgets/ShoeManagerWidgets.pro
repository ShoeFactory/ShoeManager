#-------------------------------------------------
#
# Project created by QtCreator 2017-12-23T19:33:48
#
#-------------------------------------------------

QT += widgets webenginewidgets webchannel

DESTDIR += $$PWD/../bin
LIBS += -L$$PWD/../bin
include($$PWD/../ShoeManagerCore/ShoeManagerCore.pri)
include($$PWD/../ShoeManagerModel/ShoeManagerModel.pri)
include($$PWD/../ShoeManagerNetwork/ShoeManagerNetwork.pri)

CONFIG += c++11
msvc:QMAKE_CXXFLAGS += -execution-charset:utf-8
msvc:QMAKE_CXXFLAGS += -source-charset:utf-8

TARGET = ShoeManagerWidgets
TEMPLATE = lib

DEFINES += SHOEMANAGERWIDGETS_LIBRARY

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
    AccountEditorUI.cpp \
    AccountLoginWidget.cpp \
    AccountPasswdWidget.cpp \
    AccountRegisterWidget.cpp \
    BMapContainer.cpp \
    BMapControlPanel.cpp \
    BMapDataCenter.cpp \
    MainWidget.cpp \
    SettingManagerUI.cpp \
    SettingProfileEditorUI.cpp \
    SettingDeviceEditor.cpp \
    ShoeDeviceListModel.cpp \
    SettingDeviceAddDialog.cpp

HEADERS += \
        shoemanagerwidgets_global.h \ 
    AccountEditorUI.hpp \
    AccountLoginWidget.hpp \
    AccountPasswdWidget.hpp \
    AccountRegisterWidget.hpp \
    BMapContainer.hpp \
    BMapControlPanel.hpp \
    BMapDataCenter.hpp \
    MainWidget.hpp \
    SettingManagerUI.hpp \
    SettingProfileEditorUI.hpp \
    SettingDeviceEditor.hpp \
    ShoeDeviceListModel.hpp \
    SettingDeviceAddDialog.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    websource.qrc

DISTFILES += \
    ShoeManagerWidgets.pri
