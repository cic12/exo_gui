# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = GUI
DESTDIR = ../x64/Debug
QT += core gui widgets serialport printsupport
CONFIG += debug
DEFINES += _UNICODE _ENABLE_EXTENDED_ALIGNED_STORAGE WIN64 QT_SERIALPORT_LIB QT_WIDGETS_LIB QT_PRINTSUPPORT_LIB _CRT_SECURE_NO_WARNINGS
INCLUDEPATH += ./../hebicpp/hebi-cpp/hebi/include \
    ./../hebicpp/hebi-cpp/src \
    ./../hebicpp/hebi-cpp/Eigen \
    ./../x-IMU/include \
    ./../TMSi/include \
    ./GeneratedFiles \
    ./GeneratedFiles/$(ConfigurationName)
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(GUI.pri)

win32: LIBS += -L$$PWD/./ -lhebi

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./hebi.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/./libhebi.a

win32: LIBS += -L$$PWD/./ -lhebicpp

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./hebicpp.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/./libhebicpp.a

win32: LIBS += -L$$PWD/./ -lX-IMU-API

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
