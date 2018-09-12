#-------------------------------------------------
#
# Project created by QtCreator 2015-08-22T20:04:55
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Attendance
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    student.cpp \
    filemanager.cpp

HEADERS  += mainwindow.h \
    student.h \
    filemanager.h

FORMS    += mainwindow.ui

DISTFILES +=

unix {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }
    target.path = $$PREFIX/bin
	desktop.path = $$PREFIX/share/applications/
	desktop.files += extras/Attendance.desktop
	icon.path = $$PREFIX/share/icons/hicolor/512x512/apps
	icon.files += extras/Attendance.png
	INSTALLS += desktop
    INSTALLS += target
	INSTALLS += icon
	
}