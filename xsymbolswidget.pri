INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/dialogbookmarks.h \
    $$PWD/dialogxsymbols.h \
    $$PWD/xsymbolswidget.h

SOURCES += \
    $$PWD/dialogbookmarks.cpp \
    $$PWD/dialogxsymbols.cpp \
    $$PWD/xsymbolswidget.cpp

FORMS += \
    $$PWD/dialogbookmarks.ui \
    $$PWD/dialogxsymbols.ui \
    $$PWD/xsymbolswidget.ui

!contains(XCONFIG, dialogxinfodbtransferprocess) {
    XCONFIG += dialogxinfodbtransferprocess
    include($$PWD/../XInfoDB/dialogxinfodbtransferprocess.pri)
}

DISTFILES += \
    $$PWD/LICENSE \
    $$PWD/README.md \
    $$PWD/xsymbolswidget.cmake
