project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	
	targetdir("%{wks.location}/Binaries/NirvanaEngine/%{cfg.platform}/%{cfg.buildcfg}")
	objdir("%{wks.location}/Intermediate/NirvanaEngine/%{cfg.platform}/%{cfg.buildcfg}")

	files
	{
		"Public/**.h",
		"Private/**.h",
		"Private/**.cpp"
	}
	
	includedirs
	{
		"%{wks.location}/Engine/Source/Runtime/Core/Public",
		"Public",
	}

	links
	{
		"Core"
	}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		debugformat "Default"
		editandcontinue "off"
        staticruntime "off"
		targetname "NirvanaEngine"

	filter "configurations:DebugEditor"
		runtime "Debug"
		symbols "on"
		debugformat "Default"
		editandcontinue "off"
		staticruntime "off"
		targetname "NirvanaEditor-Debug"

	filter "configurations:Development"
		runtime "Release"
		optimize "on"
		staticruntime "off"
		targetname "NirvanaEngine"

	filter "configurations:DevelopmentEditor"
		runtime "Release"
		optimize "on"
		staticruntime "off"
		targetname "NirvanaEditor-Development"

	filter "configurations:Shipping"
		runtime "Release"
		optimize "on"
		staticruntime "off"
		targetname "NirvanaEngine"


	