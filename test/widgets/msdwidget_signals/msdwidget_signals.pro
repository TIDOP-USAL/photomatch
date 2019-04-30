QT += testlib
QT += gui
QT += widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_msdwidgetsignals.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/libwidgets/release/ -llibwidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../src/libwidgets/debug/ -llibwidgets

INCLUDEPATH += $$PWD/../../src/libwidgets
DEPENDPATH += $$PWD/../../src/libwidgets

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/libwidgets/release/liblibwidgets.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/libwidgets/debug/liblibwidgets.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/libwidgets/release/libwidgets.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/libwidgets/debug/libwidgets.lib
