project "crux-common"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    staticruntime "On"

    targetdir (BinDir.. "/%{prj.name}")
    objdir (TmpDir.. "/%{prj.name}")

    pchheader "crx-pch.h"
    pchsource "crx-pch.cpp"

    files {
        "src/**.h",
        "src/**.hpp",
        "src/**.c",
        "src/**.cpp"
    }

    includedirs {
        "src",
        "src/crux-common"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "CRUX_WIN32=1"
        }