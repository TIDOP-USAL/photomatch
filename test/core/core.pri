HEADERS += \
    ../../../src/fme/fme_global.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../src/fme/core/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../src/fme/core/debug/ -lcore
else:unix:!macx: LIBS += -L$$OUT_PWD/../../../src/fme/core/ -lcore

INCLUDEPATH += $$PWD/../../src/fme/core \
               $$PWD/../../src \
               $$OUT_PWD/../../../  ## Para incluir el fichero config_fme.h

DEPENDPATH += $$PWD/../../src/fme/core

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../src/fme/core/release/libcore.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../src/fme/core/debug/libcore.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../src/fme/core/release/core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../src/fme/core/debug/core.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../../src/fme/core/libcore.a
