workspace "MyWorkspace"
    configurations {"Debug", "Release"}
    architecture "x86_64"
    startproject "MyLibrary"

project "MyLibrary"
    kind "SharedLib" --tells premake to build a DLL
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}" --intermediate directory

    files { "src/**.h", "src/**.cpp" } 

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