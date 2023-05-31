Qt LGPL app template:

STATIC/Dynamic desktop/mobile LGPL friendly APP template.

This is a project template with the LGPL license in mind.

Each time you build a Release, a release.zip file is generated. This file contains a Qt project with the following structure:

- Your closed-source project compiled into a static library (libprivateProject.a/privateProject.lib)
- All additional LGPL libraries that must be rebuilt into your project
- A very simple main.c that calls your app's _main()
- All "magic" dependencies— the Qt build system needs information about your project for a successful rebuild

## How to SETUP a project:

1. Choose a name for your project, without any blank spaces. For example, 'MYappName'.
2. Edit config.pri and insert your desired target project name. For example:


    #config.pri
    #CUSTOM PARAMETERS
    #PUT PROJECT TARGET NAME HERE.
    #USE SAME NAME FOR PROJECT MAIN FOLDER
    TARGET=MYappName


You can configure the release.zip feature:
-> Generate a separate release.zip in the build folder  (ADDZIPTORESOURCES=no)
-> Embed the release.zip file into the final executable (ADDZIPTORESOURCES=yes, available in resources path ":/release.zip")

By default, the generation of release.zip is enabled only in release compilation.

3. RENAME the project folder, using the same TARGET name (this recommendation is for Android builds only, but you should do this in any qmake project to avoid the "main activity not found" issue in android).
       
       
Note: On Windows, very long or deep folder paths can be problematic for Qt /VisualStudio. Use short paths with no blank spaces, for example, c:\qtproj\MYappName

4. RENAME qmlAppTemplate.pro to your chosen TARGET name .pro

RECOMMENDED FOLDER STRUCTURE

MYappName\
-->MYappName.pro
-->config.pri  (TARGET=MYappName)
-->privateProject (closed-source project: the software will be compiled as a static library, with the _main() entry point)
-->main (main.cpp : executes the _main() function of the static library)
-->deployProject (release.zip generator)
-->publicLibs (optional, you can delete this folder, or you can put other LGPL libraries here: any source code you include here will be copied into the redistributable file to be recompiled)

## PORTING EXISTING SOFTWARE

- Keep the same software structure inside the private folder
- main.c /main.cpp must be renamed to _main.c /_main.cpp
- main function must be renamed to _main
- You must use and include main.h in your _main.c /_main.cpp
- Each resource file must be initialized in _main function
- Private main .pro file must be "privateProject.pro", with no TARGET/TEMPLATE definitions (it's a static lib, see example)
- Add all your QT+= qt modules in privateProject.pri (see example)
- Add all your external libs option in privateProject.pri (LIBS+=, etc.)

## OPTIONAL:

Additional external libs:

- You can add libraries inside the publicLibs folder (see example). These files must be recompiled with main.cpp.
- You can add some public resources to publicResources.qrc (for example, an LGPL font TTF)
- You can add any file inside the publicLibs/otherSourceCode folder. It will be compressed inside release.zip.
- You can add full Qt sources inside the publicLibs/other

SourceCode folder, but it can be slow. It's BETTER to store Qt sources in a separate file or URL.

Adding other static libs is possible, but it requires additional work.

If you don't need external libraries, just remove the publicLibs folder.

You get two templates:
- qtLGPLAppTemplateFull (with other LGPL libs, and QtLegal dialog)
- qtLGPLAppTemplateMinimal (minimal QML hello world)

Remember that an "about" dialog is mandatory in open-source licensing. The included QtLegal is a good example.

---

This is the corrected version of your readme file. You can replace your existing text with the one above.
