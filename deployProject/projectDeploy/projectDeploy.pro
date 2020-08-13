TEMPLATE = app


QT -= gui core

CONFIG += c++17
CONFIG += console



SOURCES = main.cpp



win32{
    CONFIG += static
    TARGET = projectDeployWin
}

unix{
  macx {
     TARGET = projectDeployMacx
     DEFINES += NO_STD_FILESYSTEM # MAC OS SIERRA MISSING C++17  STD:.FILESYSTEM SUPPORT
  }
  else {
     CONFIG += static
     TARGET = projectDeployLinux
     QMAKE_LFLAGS += -static -s
  }
}

HEADERS += \
    ghc/filesystem.hpp \
    ghc/fs_fwd.hpp \
    ghc/fs_impl.hpp \
    ghc/fs_std.hpp \
    ghc/fs_std_fwd.hpp \
    ghc/fs_std_impl.hpp


