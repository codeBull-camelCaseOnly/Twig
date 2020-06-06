workspace "Twig"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Twig/vendor/GLFW/include"
IncludeDir["Glad"] = "Twig/vendor/Glad/include"
IncludeDir["ImGui"] = "Twig/vendor/imgui"

include "Twig/vendor/GLFW"
include "Twig/vendor/Glad"
include "Twig/vendor/imgui"

project "Twig"
	location "Twig"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "twigpch.h"
	pchsource "Twig/src/twigpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"TWIG_PLATFORM_WINDOWS",
			"TWIG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "TWIG_DEBUG"
		buildoptions "/MDd"			 
		symbols "On"

	filter "configurations:Release"
		defines "TWIG_RELEASE"
		buildoptions "/MD"			
		optimize "On"

	filter "configurations:Dist"
		defines "TWIG_DIST"
		buildoptions "/MD"			
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Twig/vendor/spdlog/include",
		"Twig/src"
	}

	links
	{
		"Twig" 
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"TWIG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TWIG_DEBUG"
		buildoptions "/MDd"					 
		symbols "On"

	filter "configurations:Release"
		defines "TWIG_RELEASE"
		buildoptions "/MD"			
		optimize "On"

	filter "configurations:Dist"
		defines "TWIG_DIST"
		buildoptions "/MD"			
		optimize "On"
