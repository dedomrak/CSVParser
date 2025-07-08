TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        csvparser.cpp \
        main.cpp \
        support_funcs.cpp

HEADERS += \
      support_funcs.h \
      csvparser.h
