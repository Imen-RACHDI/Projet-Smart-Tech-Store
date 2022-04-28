QT += core gui
QT += core gui
QT += multimediawidgets
QT += multimedia
QT += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += core gui sql

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets
QT += printsupport

TARGET = smtp
TEMPLATE = app


CONFIG += c++11
QT += multimedia
QT += printsupport
QT += widgets
QT       += core gui sql multimedia printsupport  network serialport

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    amenn.cpp \
    arduino.cpp \
    client.cpp \
    connection.cpp \
    exportexcelobjec.cpp \
    fournisseurs.cpp \
    main.cpp \
    piechartwidget.cpp \
    qrcode.cpp \
    reclamation.cpp \
    smtp.cpp \
    statistique.cpp

HEADERS += \
    amenn.h \
    arduino.h \
    client.h \
    connection.h \
    exportexcelobjec.h \
    fournisseurs.h \
    piechartwidget.h \
    qrcode.h \
    reclamation.h \
    smtp.h \
    statistique.h

FORMS += \
    ../Atelier_Connexion/statistique.ui \
    amenn.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
