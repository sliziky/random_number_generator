TEMPLATE = app
TARGET = Random_Number_Generator

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES +=  src\main.cpp \
   src\main.cpp \
    src\generator.cpp

HEADERS += \
    src\generator.h \
    src\config.h
