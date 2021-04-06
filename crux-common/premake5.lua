project "crux-common"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    staticruntime "On"

    targetdir (BinDir.. "/%{prj.name}")
    objdir (TmpDir.. "/%{prj.name}")

    files {
        "crx-pch.h",
        "crx-pch.cpp",
        "include/**.h",
        "include/**.hpp",
        "src/**.c",
        "src/**.cpp"
    }

    includedirs {
        "include"
    }

    filter "system:windows"
        removefiles {
            "**.nix.h"
            "**.nix.cpp"
            "**.mac.h"
            "**.mac.cpp"
        }

    filter ""