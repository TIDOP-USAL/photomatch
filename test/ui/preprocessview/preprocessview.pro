QT += testlib
QT += gui widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_preprocessview.cpp \
    ../../../src/fme/ui/PreprocessView.cpp

HEADERS += \
    ../../../src/fme/ui/mvp.h \
    ../../../src/fme/ui/PreprocessView.h

INCLUDEPATH += $$PWD/../../../src
