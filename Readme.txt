
Qt  LGPL app template :

STATIC/Dinamic desktop/mobile LGPL friendly APP template

project template with LGPL license in mind.



Each time you build a Release , a release.zip file is generated.

This file contain a Qt project with this structure:

-your closed source project compiled into a static library
-all aditional LGPL libraries that must be  rebuild into your project
-a very simple main.c
-all "magic" dependecies.














How to MIGRATE your existing project:
1. in windows, dont use spaces in project folder

c:\users\users\my projects\qmlAppTemplate  <---KO
c:\users\users\my_projects\qmlAppTemplate  <---OK

2.edit config.pri and 

2.1 put your desired target project name
example:

#config.pri
#CUSTOM PARAMETERS
#PUT PROJECT TARGET NAME HERE.
#USE SAME NAME FOR PROJECT MAIN FOLDER
TARGET=myQmlAppTemplate


2.2 
You can generate a separated release.zip in build folder  (ADDZIPTORESOURCES=no)

or you can incrustate release.zip file into final executable (ADDZIPTORESOURCES=yes, available in resource in ":/release.zip")

By default, generation of release.zip is enabled in release compilation only.



3. Rename main project folder to TARGET name (Very important for iOS/Android deploy)
example:
rename
c:\users\users\my_projects\qmlAppTemplate
to
c:\users\users\my_projects\myQmlAppTemplate

4. rename qmlAppTemplate.pro to target_name.pro

example

c:\users\users\my_projects\myQmlAppTemplate\qmlAppTemplate.pro  --> c:\users\users\my_projects\myQmlAppTemplate\myQmlAppTemplate.pro

5. Integrate your sourcecode into privateProject folder

copy content of you .pro project file into privateProject.pro
AFTER #END MANDATORY CONFIGURATION line

coment ALL TEMPLATE & TARGET lines
example
#TEMPLATE = app
#TARGET = sidepanel

Comment all Qt modules references
#QT += quick
and paste it inside privateProjectQtModules.pri



6. EDIT your provate project main.c file 
6.1
add this includes
#include "main.h" //ADD THIS INCLUDE
#include "QtLegal.h" //optional Qt legal widget

6.2 rename main to _main
int _main(int argc, char *argv[]) //rename main to _main

6.3 after main declaration ,register all resource files used in your software
    //add  your resource files here
    Q_INIT_RESOURCE(qml);//FORCE LINK RESOURCES IN STATIC LIBRARY ..."qml.qrc"

6.4 Optional: declare QML legal widget, after QGuiApplication declaration

    QtLegal::instance()->setVersionData(BUILD_VERSION,BUILD_DATE,":/CHANGELOG.txt");



7. Optional: add all project LGPL libraries and modules into publicLibs/publicLibs.pri
example: QtLegal is a LGPL library, and will be packet inside release.zip

