QT += testlib
QT += gui widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_newsessionview.cpp \
    ../../../src/fme/ui/NewSessionView.cpp

HEADERS += \
    ../../../src/fme/ui/NewSessionView.h \
    ../../../src/fme/ui/mvp.h

INCLUDEPATH += $$PWD/../../../src
