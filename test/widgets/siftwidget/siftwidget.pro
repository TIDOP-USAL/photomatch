QT += testlib
QT += gui
QT += widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_siftwidget.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../src/fme/widgets/release/ -llibwidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../src/fme/widgets/debug/ -llibwidgets
else:unix:!macx: LIBS += -L$$OUT_PWD/../../../src/fme/widgets/ -llibwidgets

INCLUDEPATH += $$PWD/../../../src/fme/widgets \
               $$PWD/../../../src
DEPENDPATH += $$PWD/../../../src/fme/widgets

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../src/fme/widgets/release/liblibwidgets.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../src/fme/widgets/debug/liblibwidgets.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../src/fme/widgets/release/libwidgets.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../src/fme/widgets/debug/libwidgets.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../../src/fme/widgets/liblibwidgets.a
