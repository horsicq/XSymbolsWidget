INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/dialogbookmarks.h \
    $$PWD/dialogxsymbols.h \
    $$PWD/xsymbolswidget.h \
    $$PWD/xmodel_xsymbol.h

SOURCES += \
    $$PWD/dialogbookmarks.cpp \
    $$PWD/dialogxsymbols.cpp \
    $$PWD/xsymbolswidget.cpp \
    $$PWD/xmodel_xsymbol.cpp

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
