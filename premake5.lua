workspace "Arcnum"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "Arcnum"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

VULKAN_SDK = os.getenv("VULKAN_SDK")

project "Spark"
    location "Spark"
    kind "StaticLib"
    language "C"
    cdialect "C17"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files {
        "Spark/src/**.h",
        "Spark/src/**.c"
    }

    includedirs {
        "include",
        "%{VULKAN_SDK}/Include"  -- Vulkan SDK headers
    }

    libdirs {
        "%{VULKAN_SDK}/Lib"  -- Vulkan SDK libraries
    }

    links {
        "opengl32.lib",
        "winmm.lib",
        "imm32.lib",
        "version.lib",
        "setupapi.lib",
        "lib/glfw3.lib",
        "vulkan-1.lib"
    }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "NDEBUG"
        runtime "Release"
        optimize "on"


project "Arcnum"
    location "Arcnum"
    kind "ConsoleApp"
    language "C"
    cdialect "C17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files {
        "Arcnum/src/**.h",
        "Arcnum/src/**.c"
    }

    includedirs {
        "Spark"
    }

    libdirs {
        "%{VULKAN_SDK}/Lib"  -- Vulkan SDK libraries
    }

    links {
        "bin/" .. outputdir .. "/Spark"
    }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "NDEBUG"
        runtime "Release"
        optimize "on"
