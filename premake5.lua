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
    cppdialect "C++17"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files {
        "Spark/src/**.h",
        "Spark/src/**.c",
        "Spark/src/**.cpp"
    }

    includedirs {
        "include",
        "%{VULKAN_SDK}/Include"  -- Vulkan SDK headers
    }

    libdirs {
        "%{VULKAN_SDK}/Lib"  -- Vulkan SDK libraries
    }

    defines { "AL_LIBTYPE_STATIC"}

    links {
        "opengl32.lib",
        "winmm.lib",
        "imm32.lib",
        "version.lib",
        "setupapi.lib",
        "lib/glfw3.lib",
        "vulkan-1.lib",
        "ws2_32.lib",
        "Avrt.lib",  
    }

    filter "configurations:Debug"
        defines { "DEBUG", "_ITERATOR_DEBUG_LEVEL=2" }
        runtime "Debug"
        symbols "on"
        links {
            "glslangd.lib",            -- Debug versions
            "SPIRVd.lib",
            "SPIRV-Toolsd.lib",
            "SPIRV-Tools-optd.lib",
            "OSDependentd.lib",
            "lib/OpenAL32D.lib",
        }

    filter "configurations:Release"
        defines { "NDEBUG", "_ITERATOR_DEBUG_LEVEL=0" }
        runtime "Release"
        optimize "on"
        links {
            "glslang.lib",             -- Release versions
            "SPIRV.lib",
            "SPIRV-Tools.lib",
            "SPIRV-Tools-opt.lib",
            "OSDependent.lib",
            "lib/OpenAL32.lib"
        }


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
        "Spark/src"
    }

    links {
        "Spark"
    }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "NDEBUG"
        runtime "Release"
        optimize "on"

    postbuildcommands {
        "{COPY} %{wks.location}/lib/*.dll %{cfg.targetdir}"
    }