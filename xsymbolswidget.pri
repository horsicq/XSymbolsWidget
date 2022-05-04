INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

FORMS += \
    $$PWD/dialogxsymbols.ui \
    $$PWD/xsymbolswidget.ui

HEADERS += \
    $$PWD/dialogxsymbols.h \
    $$PWD/xsymbolswidget.h

SOURCES += \
    $$PWD/dialogxsymbols.cpp \
    $$PWD/xsymbolswidget.cpp

!contains(XCONFIG, dialogxinfodbtransferprocess) {
    XCONFIG += dialogxinfodbtransferprocess
    include($$PWD/../XInfoDB/dialogxinfodbtransferprocess.pri)
}

DISTFILES += \
    $$PWD/LICENSE \
    $$PWD/README.md \
    $$PWD/xsymbolswidget.cmake
