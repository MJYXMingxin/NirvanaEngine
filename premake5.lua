include "./Programs/ThirdParty/premake/customization/solution_items.lua"

workspace "NirvanaEngine"
	architecture "x64"
	startproject "Sandbox"
	characterset ("MBCS")
	cppdialect "C++20"

	configurations
	{
		"Debug",
		"DebugEditor",
		"Development",
		"DevelopmentEditor",
		"Shipping"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	platforms
    {
        "Win64",
    }

	filter "platforms:Win64"
        system "Windows"
        architecture "x86_64"

	filter "configurations:Debug"
		defines
		{
			"NIRVANA_CORE_EXPORTS",
			"BUILD_DEBUG",
			"WITH_EDITOR=0"
		}
		runtime "Debug"
		symbols "on"

	filter "configurations:DebugEditor"
		defines
		{
			"BUILD_DEBUG",
			"WITH_EDITOR=1"
		}
		runtime "Debug"
		symbols "on"

	filter "configurations:Development"
		defines
		{
			"BUILD_DEVELOPMENT",
			"WITH_EDITOR=0"
		}
		runtime "Release"
		optimize "on"

	filter "configurations:DevelopmentEditor"
		defines
		{
			"BUILD_DEVELOPMENT",
			"WITH_EDITOR=1"
		}
		runtime "Release"
		optimize "on"

	filter "configurations:Shipping"
		defines
		{
			"BUILD_SHIPPING",
			"WITH_EDITOR=0"
		}
		runtime "Release"
		optimize "on"

group "Engine/Source/Runtime"
	include "Engine/Source/Runtime/Core"
group ""

group "Engine/Source/ThirdParty"
	include "Engine/Source/ThirdParty/mimalloc"
group ""

group "Programs"
	include "Programs/ThirdParty/premake"
group ""

group "Game"
	include "Game/Sandbox"
group ""