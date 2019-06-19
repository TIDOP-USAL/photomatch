QT += testlib
QT += gui
QT += widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

DEFINES += QT_PROJECT

SOURCES +=  tst_rswhewidgetsignals.cpp

include(..\widgets_test.pri)
