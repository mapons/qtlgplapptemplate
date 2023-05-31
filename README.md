# Qt LGPL App Template 

The Qt LGPL application template allows you to create PROPRIETARY SOFTWARE using the free QT LGPL. It helps you create 100% compatible desktop and mobile applications using LGPLv3 libraries.

## With this template you get:

A qmake sample project template that builds proprietary source code into a static library (.a / .lib), PROTECTING YOUR SOURCE CODE, and creates a redistributable project in a .zip file (this happens on every release build).

The release.zip file can be recompiled by any user to exercise their rights under the LGPL 3.0 license.

You can add other LGPL 3.0 library sources to the project that will be added to the redistributable project.

This template supports static compilation: you can develop an application with static compilation, because users can always easily recompile their application executable.

IOS / Android Compatibility: You can create an LGPL compatible mobile app for iOS and Android. On these platforms, users cannot replace LGPL Libraries (an LGPL 3.0 requirement), but they can recompile the mobile app and install it on their own mobile device.

There is the possibility of embedding the release.zip file in the application's own resources, enabling it to be downloaded from an "about" dialog.

Multiplatform: the project uses an executable to prepare the release file, which is included statically linked for the Windows 32/64, Linux 64 and MacOS platforms. It has been tested on Windows, Linux Ubuntu 20.04, MacOS Sierra, and Android.

A sample QML "about" dialog is included, to list the licenses used (a requirement of most open source licenses), and to add the download URL of your release.zip file.

Limitations: If you use the QML compiler, your application can only be recompiled with the same minor version of Qt (for example, a Qt 5.15.0 application cannot be linked to another version of Qt, like Qt 5.15.1).

[Template HowTo](https://dianiuxinnova.com/RESOURCES/ReadmeQtLGPL_AppTemplate.txt)

## See it in action

[![Example video](http://img.youtube.com/vi/dWubwoOzjlw/0.jpg)](http://www.youtube.com/watch?v=dWubwoOzjlw)

- [Release files examples (Windows)](https://github.com/dianiux-innova/qtlgplapptemplateExamples/tree/master/windows)
- [Release files examples (Linux 64)](https://github.com/dianiux-innova/qtlgplapptemplateExamples/tree/master/linux-X86_64)
- [Release files examples (MacOS)](https://github.com/dianiux-innova/qtlgplapptemplateExamples/tree/master/macos)
- [Release files examples (Android)](https://github.com/dianiux-innova/qtlgplapptemplateExamples/tree/master/android)
- [Static Windows 32 bits Qt5 demo application with self-contained release.zip](https://github.com/dianiux-innova/qtlgplapptemplateExamples/raw/master/windows/qtLgplAppTemplate_Static_Build_selfContained_release_zip.7z)

Android App using Qt LGPL App Template on Google Play:

- [DoubleEmoji on Google Play](https://play.google.com/store/apps/details?id=com.dianiuxinnova.doubleemoji)
- [DoubleEmoji project redistributables](https://github.com/dianiux-innova/doubleemoji)

## About

Miguel Angel Pons, Dianiux Innova SL

<https://www.dianiuxinnova.com>
<qtmarketplace@dianiuxinnova.com>


