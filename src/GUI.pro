#-------------------------------------------------
#
# Project created by QtCreator 2016-12-07T23:41:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Driver.cpp \
    stack.cpp \
    avl.cpp \
    list.cpp \
    trie.cpp \
    tst.cpp \
    file.cpp \
    data.cpp \
    HashTable.cpp \
    LinkedList.cpp

HEADERS  += mainwindow.h \
    stack.h \
    avl.h \
    list.h \
    trie.h \
    tst.h \
    file.h \
    data.h \
    HashTable.h \
    LinkedList.h

FORMS    += mainwindow.ui
