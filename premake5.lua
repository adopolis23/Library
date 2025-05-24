workspace "MyWorkspace"
    configurations {"Debug", "Release"}
    architecture "x86_64"
    startproject "Application"

project "MyLibrary"
    kind "SharedLib" --tells premake to build a DLL
    language "C++"
    cppdialect "C++17"
    targetdir "Library/bin/%{cfg.buildcfg}"
    objdir "Library/bin-int/%{cfg.buildcfg}" --intermediate directory

    files { "Library/src/**.h", "Library/src/**.cpp" } 

    filter "system:windows"
        systemversion "latest"
    
    filter "configurations:Debug"
        defines { "DEBUG" }  
        symbols "On"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
    
    filter "configurations:*"
        defines { "LIBRARY_BUILD_DLL" } --this to be used for macros when defining __declspec(dllexport)


-- Client EXE project
project "Application"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "Application/bin/%{cfg.buildcfg}"
    objdir "Application/bin-int/%{cfg.buildcfg}"

    files { "Application/src/**.cpp" }

    includedirs { "Library/src" }
    --links { "MyLibrary" }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    
    --dont need the dll or lib as this is all a template in a header
    --postbuildcommands {
        --'{COPY} "%{wks.location}/Library/bin/%{cfg.buildcfg}/MyLibrary.dll" "%{cfg.targetdir}"'
    --}

-- === GoogleTest ===
project "gtest"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    targetdir "Tests/bin/%{cfg.buildcfg}"
    objdir "Tests/bin-int/%{cfg.buildcfg}"
    files { "external/googletest/googletest/src/**.cc" }
    includedirs { "external/googletest/googletest/include", "external/googletest/googletest" }

-- === Test Project ===
project "MyLibraryTests"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "Tests/bin/%{cfg.buildcfg}"
    objdir "Tests/bin-int/%{cfg.buildcfg}"
    files { "Tests/src/**.cpp", "Tests/src/**.h" }

    includedirs {
        "Library/src",
        "external/googletest/googletest/include"
    }

    links {
        --"MyLibrary",
        "gtest"
    }