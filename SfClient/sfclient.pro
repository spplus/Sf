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
} 

INCLUDEPATH += ../common/include

QT += core gui widgets network phonon
#CONFIG += console

TARGET = ../../bin/SfClient
TEMPLATE = app
RESOURCES = sfclient.qrc
RC_FILE=sfclient.rc
SOURCES += main.cpp\
    mainwindow.cpp \
	../common/include/qhttp/qhttpnetwork.cpp \
	userlogindlg.cpp \
	configer.cpp \
	gocontroller.cpp \
	topwidget.cpp \
	titlewidget.cpp \
	netclient.cpp \
	../common/include/jsoncpp/json_internalarray.inl \
	../common/include/jsoncpp/json_internalmap.inl \
	../common/include/jsoncpp/json_reader.cpp \
	../common/include/jsoncpp/json_value.cpp \
	../common/include/jsoncpp/json_valueiterator.inl \
	../common/include/jsoncpp/json_writer.cpp
	

    
HEADERS  += mainwindow.h \
			../common/include/qhttp/qhttpnetwork.h \
			userlogindlg.h \
			common.h \	
			configer.h \
			gocontroller.h \
			topwidget.h \
			titlewidget.h \
			netclient.h \
			../common/include/jsoncpp/autolink.h \
			../common/include/jsoncpp/config.h \
			../common/include/jsoncpp/features.h \
			../common/include/jsoncpp/forwards.h \
			../common/include/jsoncpp/json.h \
			../common/include/jsoncpp/json_batchallocator.h \
			../common/include/jsoncpp/reader.h \
			../common/include/jsoncpp/value.h \
			../common/include/jsoncpp/writer.h
			
    


