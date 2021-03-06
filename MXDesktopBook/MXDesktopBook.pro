QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

MX_GITHUB_PATH = $${PWD}/../../

INCLUDEPATH += $${MX_GITHUB_PATH}/MXToolkit/common/
INCLUDEPATH += $${MX_GITHUB_PATH}/MXToolkit/webrequest/

INCLUDEPATH += $${MX_GITHUB_PATH}/MiniBlink/
INCLUDEPATH += $${MX_GITHUB_PATH}/MXPython/


#message ($${INCLUDEPATH})


SOURCES += \
    desktopbookwidget.cpp \
    main.cpp

HEADERS += \
    desktopbookwidget.h

FORMS += \
    desktopbookwidget.ui

RC_ICONS = logo.ico

VERSION = 1.0.0.202001081800
QMAKE_TARGET_PRODUCT = MXDesktopBook
QMAKE_TARGET_COMPANY = www.wasai.life
QMAKE_TARGET_DESCRIPTION = MXDesktopBook
QMAKE_TARGET_COPYRIGHT = www.wasai.life

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
