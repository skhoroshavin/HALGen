TARGET = HALGen
TEMPLATE = app

CONFIG   += console
QT       += core

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    AvrGPIO.cpp \
    FileUtils.cpp \
    HalGen.cpp \
    HalGPIO.cpp \
    HalDevice.cpp \
    CodeGenerator.cpp

HEADERS += \
    AvrGPIO.h \
    FileUtils.h \
    HalGen.h \
    HalGPIO.h \
    HalDevice.h \
    CodeGenerator.h

RESOURCES += \
    HALGen.qrc
