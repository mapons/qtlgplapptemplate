#CUSTOM PARAMETERS
##TARGET NAME.
#USE SAME NAME FOR PROJECT MAIN FOLDER
#USE SAME NAME FOR deployProject.pro APPTARGET
#USE SAME NAME FOR main.pro TARGET
exists($$PWD/config.pri) {
    include($$PWD/config.pri)
} else{
    exists($$PWD/../config.pri) {
        include($$PWD/../config.pri)
    }
}

#TARGET = $$APPTARGET
#END CUSTOM PARAMETERS
win32{
}else{
unix{
}else{
#WEBASSEMBLY
QMAKE_LFLAGS += '-s TOTAL_MEMORY=1500mb -s TOTAL_STACK=1200mb'
}
}

CONFIG += c++14
#MANDATORY
TEMPLATE = app
SOURCES += main.cpp
RESOURCES += main.qrc # project dependencies
#OPTIONAL: ADD RELEASE.zip project library in resources
contains(ADDZIPTORESOURCES, 'yes'):{
  contains(GENERATEZIP, 'yes'):{
    exists($$PWD/release.zip){
      message("ADDING RELEASE.ZIP TO RESOURCES")
      RESOURCES +=  builder.qrc
    }
  }
}

DISTFILES += builder.qrc # DIST FILES ONLY

#APP ICON
RC_ICONS = icon.ico #ICONO
ICON = icon.ico



#LINK STATIC LIB FOR PRIVATE PROJECT
#add Qt modules used in yout static library
exists($$PWD/privateProjectQtModules.pri) {
    include($$PWD/privateProjectQtModules.pri)
} else{
    exists($$PWD/../privateProject/privateProjectQtModules.pri) {
        include($$PWD/../privateProject/privateProjectQtModules.pri)
    }else{
        message("ERROR: privateProjectQtModules.pri NOT FOUND")
    }
}

#link static library
win32:LIBS += -L$$PWD/  # main distributable release
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../privateProject/release/ -lprivateProject
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../privateProject/debug/ -lprivateProject

unix{
        android{
            LIBS += -L$$OUT_PWD/../privateProject/ -L$$PWD/  -lprivateProject_$${QT_ARCH} # fichero copiado en la carpeta de deploy
        }else{
            LIBPRIVATE=$$OUT_PWD/../privateProject/libprivateProject.a
            !exists($$OUT_PWD/../privateProject/libprivateProject.a ) {
                    message( "Configuring local libprivateProject.a" )
                    exists($$PWD/libprivateProject.a ){
                        LIBPRIVATE= $$PWD/libprivateProject.a
                    }
             }
            LIBS += $$LIBPRIVATE
            PRE_TARGETDEPS += $$LIBPRIVATE
        }
}
exists($$PWD/../privateProject){
 INCLUDEPATH += $$PWD/../privateProject
 DEPENDPATH += $$PWD/../privateProject
}


#android{
    #DEFINES += LIBS_SUFFIX='\\"_$${QT_ARCH}.so\\"'
    #QT += androidextras
#}


#Add sources for open other open source LGPL libraries
#OPTIONAL  LPGL EXTERNAL LIBRARIES
exists($$PWD/publicLibs/publicLibs.pri) {
   include($$PWD/publicLibs/publicLibs.pri)
} else{
    exists($$PWD/../publicLibs/publicLibs.pri) {
      include($$PWD/../publicLibs/publicLibs.pri)
    }
}
#END ADD OPTIONAL  LPGL EXTERNAL LIBRARIES

#END PRIVATE PROJECT

#END MANDATORY












