#-------------------------------------------------
#
# Project created by QtCreator 2018-11-11T10:54:12
#
#-------------------------------------------------

QT       += core gui

QT +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AndroidOnAduino
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dialog.cpp \
    SwitchControl.cpp

HEADERS += \
        mainwindow.h \
    dialog.h \
    SwitchControl.h

FORMS += \
        mainwindow.ui \
    dialog.ui

CONFIG += mobility
MOBILITY = 

DISTFILES += \
    Resource/close.png \
    Resource/open.png \
    android/AndroidManifest.xml

RESOURCES += \
    image.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

