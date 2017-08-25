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
    editors/sqltablewin.cpp \
    clipboard/clipboardworker.cpp \
    editors/sqlrelationaltablemodel.cpp \
    editors/outertexttable.cpp \
    editors/keywordseditor.cpp \
    editors/patteditor.cpp \
    editors/parameditor.cpp \
    editors/prodeditor.cpp \
    editors/manufacturerseditor.cpp \
    editors/multiplicyeditor.cpp \
    product-selection/productconstructor.cpp \
    product-selection/productvariety.cpp \
    import/nomenclatureimport.cpp \
    product-selection/productinfomodel.cpp \
    product-selection/product.cpp \
    product-selection/multiplechoice.cpp

HEADERS  += mainwindow.h \
    import/importdata.h \
    import/nomenclature.h \
    import/priceimport.h \
    sql/sqlconn.h \
    delegates/sqlinsdelegate.h \
    sql/sqlquery.h \
    sqltableviewwindow.h \
    editors/sqltablewin.h \
    clipboard/clipboardworker.h \
    editors/sqlrelationaltablemodel.h \
    editors/outertexttable.h \
    editors/keywordseditor.h \
    editors/patteditor.h \
    editors/parameditor.h \
    editors/prodeditor.h \
    editors/manufacturerseditor.h \
    editors/multiplicyeditor.h \
    product-selection/productconstructor.h \
    product-selection/productvariety.h \
    import/nomenclatureimport.h \
    product-selection/productinfomodel.h \
    product-selection/product.h \
    product-selection/multiplechoice.h

FORMS    += mainwindow.ui \
    sqltablewin.ui \
    importdata.ui \
    product-selection/multiplechoice.ui

RESOURCES += \
    images/resource.qrc
