include_directories(${CMAKE_CURRENT_LIST_DIR})

if (NOT DEFINED DIALOGXINFODBTRANSFERPROCESS_SOURCES)
    include(${CMAKE_CURRENT_LIST_DIR}/../XInfoDB/dialogxinfodbtransferprocess.cmake)
    set(XSYMBOLSWIDGET_SOURCES ${XSYMBOLSWIDGET_SOURCES} ${DIALOGXINFODBTRANSFERPROCESS_SOURCES})
endif()

set(XSYMBOLSWIDGET_SOURCES
    ${XSYMBOLSWIDGET_SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/xsymbolswidget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/xsymbolswidget.h
    ${CMAKE_CURRENT_LIST_DIR}/xsymbolswidget.ui
    ${CMAKE_CURRENT_LIST_DIR}/dialogbookmarks.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dialogbookmarks.h
    ${CMAKE_CURRENT_LIST_DIR}/dialogbookmarks.ui
    ${CMAKE_CURRENT_LIST_DIR}/dialogxsymbols.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dialogxsymbols.h
    ${CMAKE_CURRENT_LIST_DIR}/dialogxsymbols.ui
    ${CMAKE_CURRENT_LIST_DIR}/xmodel_xsymbol.h
    ${CMAKE_CURRENT_LIST_DIR}/xmodel_xsymbol.cpp
)
