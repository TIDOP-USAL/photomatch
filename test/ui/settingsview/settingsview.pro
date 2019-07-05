QT += testlib
QT += gui widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_settingsview.cpp \
    ../../../src/fme/ui/SettingsView.cpp

HEADERS += \
    ../../../src/fme/ui/mvp.h \
    ../../../src/fme/ui/SettingsView.h

INCLUDEPATH += $$PWD/../../../src
