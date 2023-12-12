QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cell.cpp \
    field.cpp \
    gamewidget.cpp \
    generator.cpp \
    main.cpp \
    solver.cpp

HEADERS += \
    cell.h \
    field.h \
    gamewidget.h \
    generator.h \
    solver.h

FORMS += \
    gamewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    1Field0.txt \
    1Field1.txt \
    1Field2.txt \
    1Field3.txt \
    1Field4.txt \
    1Field5.txt \
    1Field6.txt \
    1Field7.txt \
    1Field8.txt \
    1Field9.txt \
    2Field0.txt \
    2Field1.txt \
    2Field2.txt \
    2Field3.txt \
    2Field4.txt \
    2Field5.txt \
    2Field6.txt \
    2Field7.txt \
    2Field8.txt \
    2Field9.txt \
    3Field0.txt \
    3Field1.txt \
    3Field2.txt \
    3Field3.txt \
    3Field4.txt \
    3Field5.txt \
    3Field6.txt \
    3Field7.txt \
    3Field8.txt \
    3Field9.txt \
    file
