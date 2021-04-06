workspace "crux"
    configurations { "debug", "release" }
    architecture "x86_64"

    flags { "MultiProcessorCompile" }

    defines {
        "CRUX_PLATFORM=\"None\"",
        "CRUX_WIN32=0",
        "CRUX_UNIX=0",
        "CRUX_MAC=0",
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "CRUX_PLATFORM=\"Win32\"",
            "CRUX_WIN32=1"
        }

    filter ""

RootDir = "%{wks.location}"
BinDir = (RootDir.. "/bin/%{cfg.architecture}/%{cfg.buildcfg}")
TmpDir = (RootDir.. "/tmp/%{cfg.architecture}/%{cfg.buildcfg}")

include "crux-common"
include "crux-window"
include "crux-example"