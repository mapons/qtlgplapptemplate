put each license file that you want to show in YOUR PROJECT qt resources, in this folder
qrc:/qtlegal/SoftwareLicenses/


you can add your own Qt licenses files (html or txt)
Qt LGPL and this module QTLegal licenses are included


USAGE

declare QML component in main function:

#include "legal.h"

and
Legal::instance()->setVersionData(BUILDVERSION,BUILD_DATE,":/CHANGELOG_FILE.txt");

example
Legal::instance()->setVersionData("v1","2020/01/01",""); //no changelog file
Legal::instance()->setVersionData("v1","2020/01/01",":/CHANGELOG_FILE.txt");
etc



In QML, you can use LicenceBrowser.qml (qrc:/qtlegal/LicenseBrowser.qml)

import 'qrc:/qtlegal/'

LicenceBrowser{


}



