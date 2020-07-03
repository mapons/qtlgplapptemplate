TEMPLATE = app


QT -= gui core

CONFIG += c++17
CONFIG += console



SOURCES = main.cpp


win32{
    CONFIG += static
    TARGET = qmlScannerWin
}

unix{
  macx {
     TARGET = qmlScannerMacx
     DEFINES += NO_STD_FILESYSTEM # MAC OS SIERRA MISSING C++17  STD:.FILESYSTEMN SUPPORT
  }
  else {
     CONFIG += static
     TARGET = qmlScannerLinux
     QMAKE_LFLAGS_RELEASE += -static
  }


}

HEADERS += \
    ghc/filesystem.hpp \
    ghc/fs_fwd.hpp \
    ghc/fs_impl.hpp \
    ghc/fs_std.hpp \
    ghc/fs_std_fwd.hpp \
    ghc/fs_std_impl.hpp

