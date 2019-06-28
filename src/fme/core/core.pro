#-------------------------------------------------
#
# Project created by QtCreator 2019-06-19T09:52:43
#
#-------------------------------------------------

QT       -= gui

TARGET = core
TEMPLATE = lib

DEFINES += QT_PROJECT

include(..\..\..\config.pri)

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

INCLUDEPATH += ../../ \
               $$OUT_PWD/../../../  ## Para incluir el fichero config_fme.h

SOURCES += \
    project.cpp \
    image.cpp \
    settings.cpp

HEADERS += \
    project.h \
    image.h \
    settings.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
