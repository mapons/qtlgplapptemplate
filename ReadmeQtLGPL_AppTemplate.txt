Qt  LGPL app template :

STATIC/Dynamic desktop/mobile LGPL friendly APP template

Project template with LGPL license in mind.



Each time you build a Release , a release.zip file is generated.

This file contain a Qt project with this structure:

- your closed source project compiled into a static library (libprivateProject.a/privateProject.lib )
- all additional LGPL libraries that must be  rebuild into your project
- a very simple main.c that call your app _main()
- all "magic" dependencies--> Qt build system needs information about your project for a successful rebuild


How to SETUP a project:

1. Choose a name for your project, with NO blank spaces, example 'MYappName'
2. edit config.pri and put your desired target project name
example:

#config.pri
#CUSTOM PARAMETERS
#PUT PROJECT TARGET NAME HERE.
#USE SAME NAME FOR PROJECT MAIN FOLDER
TARGET=MYappName

You can configure release.zip feature:
->generate a separated release.zip in build folder  (ADDZIPTORESOURCES=no)
->incrustate release.zip file into final executable (ADDZIPTORESOURCES=yes, available in resources path ":/release.zip")

By default, generation of release.zip is enabled in release compilation only.


3. RENAME the project folder, using the same TARGET name (this recommendation is for Android builds only, but you should do this in any qmake project to avoid the "main activity not found" issue in android )
        example
        c:\users\users\my_projects\MYappName
       
       
        Note: on windows, very long or deep folder can be problematic in Qt /VisualStudio
              use short paths with no blank spaces, for example c:\qtproj\MYappName

4. RENAME qmlAppTemplate.pro to your chosen  TARGET name .pro

example

c:\my_projects\MYappName\qmlAppTemplate.pro  --> c:\my_projects\MYappName\MYappName.pro


RECOMMENDED FOLDER STRUCTURE

MYappName\
-->MYappName.pro
-->config.pri  (TARGET=MYappName)
-->privateProject (closed source project: the software will be compiled as a static library, with the _main() entry point)
-->main (main.cpp : executes the _main() function of the static library)
-->deployProject (release.zio generator)
-->publicLibs (optional, you can delete this folder, or you can put other LGPL libraries here: any source code you include here will be copied into the redistributable file to be recompiled)

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
-add all your external libs option in in privateProject.pri (LIBS+= , etc)

OPTIONAL:

additional external libs
-You can add libraries inside the publicLibs folder (see example). This files must be recompiled with main.cpp
-You can add some public resources to publicResources.qrc (for example, a LGPL font TTF)
-You can add any file inside the publicLibs/otherSourceCode folder. Will be compressed inside release.zip
-You can add full Qt sources inside the publicLibs/otherSourceCode folder, but it can be very slow.
 Is BETTER than you store Qt sources in separate file or URL

Is possible to add other static libs, but some work is required

If you don't need external libraries, jut remove publicLibs folder


You get two templates:
qtLGPLAppTemplate
-qtLGPLAppTemplateFull (with other LGPL libs, and QtLegal dialog)
-qtLGPLAppTemplateMinimal (minimal QML hello world)

Remember that an about dialog is mandatory in open source licensing. Included QtLegal is a good example


