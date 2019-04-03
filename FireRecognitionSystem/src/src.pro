#-------------------------------------------------
#
# Project created by QtCreator 2019-03-22T13:44:57
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = src
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
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Fire/release/ -lFire
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Fire/debug/ -lFire
else:unix: LIBS += -L$$OUT_PWD/../Fire/ -lFire

INCLUDEPATH += $$PWD/../Fire
DEPENDPATH += $$PWD/../Fire

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Fire/release/libFire.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Fire/debug/libFire.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Fire/release/Fire.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Fire/debug/Fire.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Fire/libFire.a
#opencv config
INCLUDEPATH +=-L $$PWD/../Fire/inc/opencv/include \
                 $$PWD/../Fire/inc/opencv/include/opencv \
                 $$PWD/../Fire/inc/opencv/include/opencv2
LIBS += $$PWD/../Fire/lib/opencv/libopencv_*.dll.a

RESOURCES += \
    imgs.qrc
