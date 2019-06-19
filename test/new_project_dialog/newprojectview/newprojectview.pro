QT += testlib
QT += gui widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_newprojectview.cpp \
    ../../../src/fme/ui/NewProjectView.cpp

HEADERS += \
    ../../../src/fme/ui/NewProjectInterfaces.h \
    ../../../src/fme/ui/NewProjectView.h \
    ../../../src/fme/ui/mvp.h

INCLUDEPATH += $$PWD/../../../src
