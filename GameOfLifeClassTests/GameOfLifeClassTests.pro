QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_gameoflifeclasstests.cpp \
    ../ConwaysGameOfLife/gameoflife.cpp

HEADERS += \
    ../ConwaysGameOfLife/gameoflife.h
