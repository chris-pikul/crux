project "crux-window"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    staticruntime "On"

    targetdir (BinDir.. "/%{prj.name}")
    objdir (TmpDir.. "/%{prj.name}")

    pchheader "crx-pch.h"
    pchsource "crx-pch.cpp"

    files {
        "crx-pch.h",
        "crx-pch.cpp",
        "include/**.h",
        "include/**.hpp",
        "src/**.c",
        "src/**.cpp"
    }

    includedirs {
        "include",

        "%{wks.location}/crux-common/include"
    }

    links {
        "crux-common"
    }

    filter "system:windows"
        removefiles {
            "**.nix.h"
            "**.nix.cpp"
            "**.mac.h"
            "**.mac.cpp"
        }

    filter ""