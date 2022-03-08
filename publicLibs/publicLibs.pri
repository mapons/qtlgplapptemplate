#dont touch it: SAVE INCLUDED FILES STATE
ORI_HEADERS= $$HEADERS
ORI_SOURCES= $$SOURCES
ORI_RESOURCES= $$RESOURCES
#INCLUDE YOUR LIBRARIES HERE-----------------------------------------------------------------
#--------------------------------------------------------------------------------------------








#example external LGPL library
include($$PWD/mainLoopWDT/mainLoopWDT.pri)









#--------------------------------------------------------------------------------------------
#dont touch it: RESTORE INCLUDED FILES STATE
#optional, public resources than can be replaced by relink user
equals(TEMPLATE , app){ # only for APP
 RESOURCES += $$PWD/publicResources.qrc
}else{
# REMOVE ALL INCLUDED FILES IN STATIC LIBRARY BUILD
 HEADERS=$$ORI_HEADERS #COMMENT THIS LINE TO SEE ^HEADERS IN PRIVATE PROJECT
 SOURCES=$$ORI_SOURCES
 RESOURCES=$$ORI_RESOURCES
}


