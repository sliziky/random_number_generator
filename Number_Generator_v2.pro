TEMPLATE = app
TARGET = Number Generator v2

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    generator.cpp

HEADERS += \
    generator.h

FORMS += \
    generator.ui
