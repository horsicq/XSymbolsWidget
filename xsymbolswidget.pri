INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

DISTFILES += \
    $$PWD/LICENSE \
    $$PWD/README.md

FORMS += \
    $$PWD/xsymbolswidget.ui

HEADERS += \
    $$PWD/xsymbolswidget.h

SOURCES += \
    $$PWD/xsymbolswidget.cpp

!contains(XCONFIG, dialogxinfodbtransferprocess) {
    XCONFIG += dialogxinfodbtransferprocess
    include($$PWD/../XInfoDB/dialogxinfodbtransferprocess.pri)
}
