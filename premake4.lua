builddir = "build"

dofile "config/premake4/functions.lua"

solution "StreamLog"
    configurations { "Debug", "Release" }

    location ( builddir )
    targetdir ( builddir )

    flags { "ExtraWarnings" }

    configuration { "linux or bsd or solaris" }
        defines { "UNIX" }

    configuration { "windows" }
        defines { "WINDOWS" }

    configuration { "linux", "gmake" }
        buildoptions { "-std=c++0x" }

    configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols" }

    configuration "Release"
        flags { "Optimize" }

    project "GeconFramework"
        kind "SharedLib"
        language "C++"

        files { "src/*.cpp" }
