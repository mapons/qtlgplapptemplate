TEMPLATE = aux
include($$PWD/../config.pri) # get TARGET
DDIR = $$OUT_PWD/../$$TARGET
RELEASEMODE=debug
CONFIG(release, debug|release): RELEASEMODE=release


ZIPFILE=""
contains(ADDZIPTORESOURCES, 'yes'):{
 ZIPFILE=$$shell_path($$PWD"/../main/release.zip") $$shell_path(../$$TARGET) # ojo, esto me lo mete en el directorio home
}else{
 ZIPFILE= $$shell_path($$OUT_PWD"/../release.zip")
}

equals(QMAKE_HOST.os, Windows) {
       SCANNERCOMMAND=projectDeployWin
} else:contains(QMAKE_HOST.os, Linux) {
       SCANNERCOMMAND=projectDeployLinux
} else:equals(QMAKE_HOST.os, Darwin) {
       SCANNERCOMMAND=projectDeployMacx
} else {
       error("Operating system not supported.")
}


makedependencies.commands = '"$$shell_path($$PWD/$$SCANNERCOMMAND)"' -f "'"$$shell_path($$PWD/../)"'" -d "'"$$shell_path($$OUT_PWD/../)"'" -p $$TARGET -r $$RELEASEMODE -z "'"$$shell_path($$ZIPFILE)"'" -v





zip.depends = makedependencies
contains(ADDZIPTORESOURCES, 'yes'):{
    equals(QMAKE_HOST.os, Windows):{
        zip.commands='"$$shell_path($$PWD/7za.exe)"' a -mx=9 -r $$shell_path($$PWD"/../main/release.zip") $$shell_path(../$$TARGET) # ojo, esto me lo mete en el directorio home
    }else{
        #zip.commands=zip -8 -r  '"$$shell_path($$PWD/../main/release.zip)"' '"$$shell_path(../$$TARGET)"' # ojo, esto me lo mete en el directorio home
        zip.commands=cd .. ;zip -9 -r  '"$$shell_path($$PWD/../main/release.zip)"' '"$$TARGET"' # ojo, esto me lo mete en el directorio home
    }
}else{
    equals(QMAKE_HOST.os, Windows):{
        zip.commands='"$$shell_path($$PWD/7za.exe)"' a -mx=9 -r  $$shell_path($$OUT_PWD"/../release.zip") $$shell_path(../$$TARGET)
    }else{
        #zip.commands=zip -7 -r  '"$$shell_path($$OUT_PWD/../release.zip)"' '"$$shell_path(../$$TARGET)"'
        zip.commands=cd .. ; zip -9 -r  release.zip '"$$TARGET"'
    }
}

contains(GENERATEZIP, 'yes'):{
 message("GENERATING release.zip FILE. QT VERSION: "$$QT_VERSION "QMAKE:" $$QMAKE_QMAKE)
 PRE_TARGETDEPS +=      makedependencies  zip
 QMAKE_EXTRA_TARGETS += makedependencies  zip
}else{
 message("SKIPING ZIP FILE")
 PRE_TARGETDEPS +=      makedependencies
 QMAKE_EXTRA_TARGETS += makedependencies
}

DISTFILES += \
    $$PWD/subdirsTemplate.pro \
    $$PWD/projectDeploy/projectDeploy.pro \
    $$PWD/qmlScanner/qmlScannerWin.sln \
    $$PWD/qmlScanner/qmlScannerWin.vcxproj \
    $$PWD/projectDeploy/main.cpp \
    $$PWD/projectDeploy/ghc/filesystem.hpp \
    $$PWD/projectDeploy/ghc/fs_fwd.hpp \
    $$PWD/projectDeploy/ghc/fs_impl.hpp \
    $$PWD/projectDeploy/ghc/fs_std.hpp \
    $$PWD/projectDeploy/ghc/fs_std_fwd.hpp \
    $$PWD/projectDeploy/ghc/fs_std_impl.hpp \
    $$PWD/projectDeployLinux \
    $$PWD/projectDeployWin.exe \
    $$PWD/projectDeployMacx \
    $$PWD/7za.dll \
    $$PWD/7zxa.dll \
    $$PWD/7za.exe \
    Vs2019/projectDeployWin.sln \
    Vs2019/projectDeployWin.vcxproj \
    Vs2019/projectDeployWin.vcxproj.filters \
    Vs2019/projectDeployWin.vcxproj.user









