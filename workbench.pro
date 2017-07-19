#-------------------------------------------------
#
# Project created by QtCreator 2017-04-25T12:06:32
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = workbench
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    sql/sqlconn.cpp \
    sql/sqlquery.cpp \
    import/importdata.cpp \
    import/priceimport.cpp \
    delegates/sqlinsdelegate.cpp \
    import/nomenclature.cpp \
    editor/sqltablewin.cpp \
    clipboard/clipboardworker.cpp \
    editor/sqlrelationaltablemodel.cpp \
    editor/outertexttable.cpp \
    editor/keywordseditor.cpp \
    editor/patteditor.cpp \
    editor/parameditor.cpp \
    editor/prodeditor.cpp \
    editor/manufacturerseditor.cpp

HEADERS  += mainwindow.h \
    import/importdata.h \
    import/nomenclature.h \
    import/priceimport.h \
    sql/sqlconn.h \
    delegates/sqlinsdelegate.h \
    sql/sqlquery.h \
    sqltableviewwindow.h \
    editor/sqltablewin.h \
    clipboard/clipboardworker.h \
    editor/sqlrelationaltablemodel.h \
    editor/outertexttable.h \
    editor/keywordseditor.h \
    editor/patteditor.h \
    editor/parameditor.h \
    editor/prodeditor.h \
    editor/manufacturerseditor.h

FORMS    += mainwindow.ui \
    sqltablewin.ui \
    importdata.ui

RESOURCES += \
    images/resource.qrc
