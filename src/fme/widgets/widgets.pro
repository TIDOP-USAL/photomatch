#-------------------------------------------------
#
# Project created by QtCreator 2019-04-09T15:32:54
#
#-------------------------------------------------

QT       -= gui

QT += widgets

TARGET = libwidgets
TEMPLATE = lib

# DEFINES +=  FME_EXPORTS
!FME_EXPORTS {
  CONFIG += staticlib
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../../

SOURCES += \
    OrbWidget.cpp \
    SiftWidget.cpp \
    SurfWidget.cpp \
    FastWidget.cpp \
    BriskWidget.cpp \
    MserWidget.cpp \
    AgastWidget.cpp \
    KazeWidget.cpp \
    AkazeWidget.cpp \
    GfttWidget.cpp \
    MsdWidget.cpp \
    DescriptorMatcherWidget.cpp \
    WallisWidget.cpp \
    CLAHEWidget.cpp \
    DaisyWidget.cpp \
    HogWidget.cpp \
    BriefWidget.cpp \
    FreakWidget.cpp \
    LatchWidget.cpp \
    LucidWidget.cpp \
    StarWidget.cpp

HEADERS += \
    OrbWidget.h \
    SiftWidget.h \
    SurfWidget.h \
    FastWidget.h \
    BriskWidget.h \
    MserWidget.h \
    AgastWidget.h \
    KazeWidget.h \
    AkazeWidget.h \
    GfttWidget.h \
    MsdWidget.h \
    DescriptorMatcherWidget.h \
    WallisWidget.h \
    CLAHEWidget.h \
    DaisyWidget.h \
    HogWidget.h \
    BriefWidget.h \
    FreakWidget.h \
    LatchWidget.h \
    LucidWidget.h \
    StarWidget.h \
    fme_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
