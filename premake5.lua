workspace "MyWorkspace"
    configurations {"Debug", "Release"}
    architecture "x86_64"
    startproject "MyLibrary"

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

    includedirs { "MyLibrary" }
    links { "MyLibrary" }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    postbuildcommands {
        '{COPY} "%{wks.location}/Library/bin/%{cfg.buildcfg}/MyLibrary.dll" "%{cfg.targetdir}"'
    }