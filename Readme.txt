
Qt  LGPL app template :

STATIC/Dinamic desktop/mobile LGPL friendly APP template

Project template with LGPL license in mind.



Each time you build a Release , a release.zip file is generated.

This file contain a Qt project with this structure:

- your closed source project compiled into a static library (libprivateProject.a/privateProject.lib )
- all aditional LGPL libraries that must be  rebuild into your project
- a very simple main.c that call your app _main()
- all "magic" dependecies--> Qt build system needs information about your project for a succesful rebuild


How to SETUP ANY project:

1. Choose a name for your project, with NO blank spaces, example 'myQmlAppTemplate'
2. edit config.pri and put your desired target project name
		example:

		#config.pri
		#CUSTOM PARAMETERS
		#PUT PROJECT TARGET NAME HERE.
		#USE SAME NAME FOR PROJECT MAIN FOLDER
		TARGET=myQmlAppTemplate
		
		You can configurate release.zip feature:
		->generate a separated release.zip in build folder  (ADDZIPTORESOURCES=no)
		->incrustate release.zip file into final executable (ADDZIPTORESOURCES=yes, available in resources path ":/release.zip")

		By default, generation of release.zip is enabled in release compilation only.

		
3. RENAME folder using the same project name (very important in Android deploy)
        example
        c:\users\users\my_projects\qmlAppTemplate  
        Note: on windows, very long or deep folder can be problematic in Qt /VisualStudio
              use short paths with no blank spaces, for example c:\qtproj\qmlAppTemplate

4. rename qmlAppTemplate.pro to your choosed target_name .pro

	example

	c:\my_projects\myQmlAppTemplate\qmlAppTemplate.pro  --> c:\my_projects\myQmlAppTemplate\myQmlAppTemplate.pro



PORTING EXISTING SOFTWARE

	-Keep the same software structure inside privateFolder
	
	-main.c /main.cpp must be renamed to _main.c /_main.cpp
	-main function must be renamed to _main
	-you must use and include main.h in your _main.c /_main.cpp
	-each resource files must be  initialized in _main function
		example
		Q_INIT_RESOURCE(privateProject);//FORCE LINK RESOURCES IN STATIC LIBRARY ..."privateProject.qrc"
	-private main .pro file must be "privateProject.pro", with no TARGET/TEMPLATE definitions (is a static libs..see example)
	-add all your QT+= qt modules in privateProject.pri (see example)
	
OPTIONAL:

aditional external libs
	-You can add libraries inside publicLibs folder (see example). This files must be recopiled with main.cpp
	-You can add some public resources to publicResources.qrc (for example, a LGPL font TTF)
	-You can add any file inside publicLibs/otherSourceCode folder. Will be compressed inside release.zip
	-You can add full Qt sources inside publicLibs/otherSourceCode folder, but can be very slow. 
	  Is BETTER than yiu store Qt sources in separate file or URL
	
Is possible to add other static libs, but some work is required

If you don't need external libraries, jut remove publicLibs folder	
	

	
	

