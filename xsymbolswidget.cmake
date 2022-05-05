include_directories(${CMAKE_CURRENT_LIST_DIR})

include(${CMAKE_CURRENT_LIST_DIR}/../XInfoDB/dialogxinfodbtransferprocess.cmake)

set(XSYMBOLSWIDGET_SOURCES
    ${DIALOGXINFODBTRANSFERPROCESS_SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/xsymbolswidget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/xsymbolswidget.ui
    ${CMAKE_CURRENT_LIST_DIR}/dialogxsymbols.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dialogxsymbols.ui
)
