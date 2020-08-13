#dont touch it: SAVE INCLUDED FILES STATE
ORI_HEADERS= $$HEADERS
ORI_SOURCES= $$SOURCES
ORI_RESOURCES= $$RESOURCES




#INCLUDE YOUR LIBRARIES HERE-----------------------------------------------------------------
#--------------------------------------------------------------------------------------------
#LGPL QTLEGAL QML WIDGET
include($$PWD/qtlegal/legal.pri)


#example external library
include($$PWD/zlib-1.2.11/zlib.pri)
DEFINES += QUAZIP_STATIC
include($$PWD/quazip-master/quazip.pri)


#EXAMPLE LIBRARY2
#include($$PWD/qrimageprovider/qrimageprovider.pri)

#EXAMPLE LIBRARY3
#include($$PWD/qrimageprovider/qrimageprovider.pri)

#--------------------------------------------------------------------------------------------










#dont touch it: RESTORE INCLUDED FILES STATE
#optional, public resources than can be replaced by relink user
equals(TEMPLATE , app){ # only for APP
 RESOURCES += $$PWD/publicResources.qrc
}else{
# REMOVE INCLUDED FILES IN STATIC LIBRARY BUILD
 #HEADERS=$$ORI_HEADERS 3 --> show headers only in privateProject
 SOURCES=$$ORI_SOURCES
 RESOURCES=$$ORI_RESOURCES
}


