QT += testlib
QT -= gui
QT += widgets
CONFIG += qt warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

DEFINES += QT_PROJECT

SOURCES +=  tst_briefwidgetssignals.cpp

include(..\widgets_test.pri)
