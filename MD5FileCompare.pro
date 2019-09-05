#-------------------------------------------------
#
# Project created by QtCreator 2019-09-02T10:41:04
#
#-------------------------------------------------

QT      += core gui
QT      += serialport
QT      += bluetooth
#QT      += webenginewidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MD5FileCompare
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        basictransceiver.cpp \
        color.cpp \
        face.cpp \
        hashtable.cpp \
        ltextedit.cpp \
        main.cpp \
        mainwindow.cpp \
        sport.cpp \
        widget.cpp

HEADERS += \
        basictransceiver.h \
        hashtable.h \
        ltextedit.h \
        mainwindow.h \
        mycv.h \
        widget.h

FORMS += \
        basictransceiver.ui \
        mainwindow.ui \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    basictransceiver.qrc


UI_DIR=./UI
RC_ICONS = huo.ico

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../Program Files/opencv/build/x64/vc15/lib/' -lopencv_world410
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../Program Files/opencv/build/x64/vc15/lib/' -lopencv_world410d
else:unix: LIBS += -L$$PWD/'../../../Program Files/opencv/build/x64/vc15/lib/' -lopencv_world410

INCLUDEPATH += $$PWD/'../../../Program Files/opencv/build/include'
DEPENDPATH += $$PWD/'../../../Program Files/opencv/build/include'

//dui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../../Program Files/opencv/build/x64/vc15/lib/' -lopencv_world410
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../../Program Files/opencv/build/x64/vc15/lib/' -lopencv_world410d

INCLUDEPATH += $$PWD/'../../../../Program Files/opencv/build/include'
DEPENDPATH += $$PWD/'../../../../Program Files/opencv/build/include'
