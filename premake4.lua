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

    project "StreamLog"
        kind "SharedLib"
        language "C++"

        files { "src/*.cpp" }

    project "ManualTests"
        kind "ConsoleApp"
        language "C++"

        targetname "manual_tests"

        require_lib("boost_thread")

        includedirs { "src" }
        includedirs { "config/manual_tests" }

        files { "config/manual_tests/*.cpp" }
        files { "test/manual_tests/*.cpp" }

        links { "StreamLog", "boost_thread" }
