#CUSTOM PARAMETERS
##PUT PROJECT TARGET NAME HERE.
#USE SAME NAME FOR PROJECT MAIN FOLDER
#NO BLANK SPACES IN NAME
TARGET=qtLgplAppTemplate


#GENERATEZIP=yes -> generates .zip distributable binary only project
#GENERATEZIP=no -> no generates .zip
CONFIG(debug, debug|release) {
#debug mode...SKIP release.zip
 GENERATEZIP=no
}else{
#release mode
 GENERATEZIP=yes
}

#add release.zip file into executable (executable doubles size!!!!)
ADDZIPTORESOURCES=no
