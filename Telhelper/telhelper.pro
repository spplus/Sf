#-------------------------------------------------
#
# Project created by QtCreator 2016-03-23T10:48:36
#
#-------------------------------------------------

win32 {
QMAKE_INCDIR_QT=$$(QTDIR)/include 
QMAKE_LIBDIR_QT=$$(QTDIR)/lib 
QMAKE_MOC=$$(QTDIR)/bin/moc.exe 
QMAKE_UIC=$$(QTDIR)/bin/uic.exe 
QMAKE_IDC=$$(QTDIR)/bin/idc.exe 
QMAKE_RCC=$$(QTDIR)/bin/rcc.exe

LIBS += -lqnviccub -L../common/lib
} 

INCLUDEPATH += ../common/include

QT += core gui widgets network
#CONFIG += console

TARGET = ../../bin/telhelper
TEMPLATE = app
RESOURCES = telhelper.qrc
RC_FILE=telhelper.rc
SOURCES += main.cpp\
    mainwindow.cpp \
	mypushbutton.cpp \
	titlewidget.cpp \
	widget.cpp
	
HEADERS  += mainwindow.h \
			../common/include/bri/BriSDKLib.h \
			../common/include/bri/BriChipErr.h \
			../common/include/bri/quviccub.h \
			mypushbutton.h \
			titlewidget.h \
			widget.h


