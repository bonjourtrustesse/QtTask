QT       += core gui 
QT += printsupport
 
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
 
SOURCES += main.cpp\
        QtTask.cpp \
        qcustomplot.cpp\
 
HEADERS  += QtTask.h \
        qcustomplot.h

FORMS   += QtTask.ui