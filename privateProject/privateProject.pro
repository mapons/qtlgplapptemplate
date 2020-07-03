#MANDATORY CONFIGURATION

TEMPLATE = lib # MUST BE LIBRARY,NOT APP
CONFIG += staticlib # MUST BE STATIC LIBRARY
CONFIG+=qtquickcompiler # PROTECT YOUR SOURCES
HEADERS += main.h
DEFINES += BUILDMAINLIB  # macro _main()
#include($$PWD/yourDotProProjectFile.pri) # YOUR ORIGINAL PRO FILE; RENAMED TO .PRI AND EDITED
include($$PWD/privateProjectQtModules.pri) # ALL QT+= FOR YOUR PROJECT




#BUILD DATE VARIABLE
contains(QMAKE_HOST.os, Windows):{
    B_TIME = $$system("date /T")_$$system("time /T")# no spaces between 'system' command and args.
}else{
    B_TIME = $$system("date '+%Y-%m-%d %H:%M:%S'")
}
DEFINES += BUILD_DATE='"\\\"$$B_TIME\\\""'
#FIN BUILD DATE


#OPTIONAL PUBLIC EXTERNAL LIBRARIES INCLUIDES ONLY
include($$PWD/../publicLibs/publicLibs.pri)

android{
    TARGET = privateProject_$${QT_ARCH}
    DEFINES += LIBS_SUFFIX='\\"_$${QT_ARCH}.so\\"'
}else{
    TARGET = privateProject
}


#END MANDATORY CONFIGURATION

#SOFTWARE VERSION MACRO
VERSION=1.04
DEFINES +=  BUILD_VERSION='"\\\"$$VERSION\\""'



#TEMPLATE = app
#TARGET = sidepanel
#QT += qml scxml --> 

# DIRECT RESOURCES MUST BE ADDED IN A RESOURCE FILE
#RESOURCES += \
#    doc/images/qtquickcontrols2-sidepanel-landscape.png \
#    doc/images/qtquickcontrols2-sidepanel-portrait.png \
#    images/qt-logo@2x.png \
#    images/qt-logo@3x.png \
#    images/qt-logo@4x.png \
#    images/qt-logo.png \
#    sidepanel.qml




CONFIG += c++11

SOURCES += calculator-qml.cpp

RESOURCES += calculator-qml.qrc  # RESOURCE FILE ... REMEMBER TO PUT Q_INIT_RESOURCE(calculator-qml); in _main() function

STATECHARTS = statemachine.scxml


