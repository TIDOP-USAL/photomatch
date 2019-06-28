QT += testlib
QT += gui
QT += widgets

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

DEFINES += QT_PROJECT

include(..\..\core\core.pri)

INCLUDEPATH += ../../../third_party

SOURCES +=  tst_mainwindowview.cpp \
    ../../../src/fme/ui/MainWindowView.cpp

FORMS += \
    ../../../src/fme/ui/MainWindowView.ui

HEADERS += \
    ../../../src/fme/ui/MainWindowView.h

