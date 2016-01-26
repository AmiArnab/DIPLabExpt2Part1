TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    bmpimage.cpp \
    readbmp.cpp \
    convertflipgrayscale.cpp \
    writebmp.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    bmpimage.h \
    readbmp.h \
    convertflipgrayscale.h \
    writebmp.h

