#VolkMilit note:
#do not blame me for this, xcb and xlib is PAIN when need to work with fonts or images
#still this app is fully optional

QT += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ra_splash
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp
