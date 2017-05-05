

win32 {
QMAKE_INCDIR_QT=$$(QTDIR)/include 
QMAKE_LIBDIR_QT=$$(QTDIR)/lib 
QMAKE_MOC=$$(QTDIR)/bin/moc.exe 
QMAKE_UIC=$$(QTDIR)/bin/uic.exe 
QMAKE_IDC=$$(QTDIR)/bin/idc.exe 
QMAKE_RCC=$$(QTDIR)/bin/rcc.exe
} 

QT += core gui widgets network
#CONFIG += console


TARGET = ../../bin/updater
TEMPLATE = app
RESOURCES = updater.qrc
RC_FILE=updater.rc
SOURCES += main.cpp \
		   mainwindow.cpp \
		   httpdownload.cpp
    
HEADERS  += mainwindow.h \
			httpdownload.h
			
			
    


