#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T15:46:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibPro_v2
TEMPLATE = app


SOURCES += main.cpp\
        loginform.cpp \
    user.cpp \
    account.cpp \
    book.cpp \
    datastore.cpp \
    guireader.cpp \
    guilibrarian.cpp

HEADERS  += loginform.h \
    user.h \
    account.h \
    book.h \
    datastore.h \
    guireader.h \
    guilibrarian.h

FORMS    += loginform.ui \
    guireader.ui \
    guilibrarian.ui
