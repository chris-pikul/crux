workspace "crux"
    configurations { "debug", "release" }
    architecture "x86_64"
    flags { "MultiProcessorCompile" }

RootDir = "%{wks.location}"
BinDir = (RootDir.. "/bin/%{cfg.architecture}/%{cfg.buildcfg}")
TmpDir = (RootDir.. "/tmp/%{cfg.architecture}/%{cfg.buildcfg}")

include "crux-common"