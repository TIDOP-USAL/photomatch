QT += testlib
QT += gui
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

DEFINES += QT_PROJECT

SOURCES +=  tst_settignsmodel.cpp \
    ../../../src/fme/ui/SettingsModel.cpp

include(..\..\core\core.pri)

HEADERS += \
    ../../../src/fme/ui/SettingsModel.h \
    ../../../src/fme/ui/mvp.h
