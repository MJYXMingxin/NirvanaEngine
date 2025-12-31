project "Core"
	kind "SharedLib"
	language "C++"
	staticruntime "off"
	
	targetname "NirvanaEngine.Core"
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
		"%{wks.location}/Engine/Source/ThirdParty/mimalloc/include",
		"Public",
		-- include mimalloc
		"../../ThirdParty/mimalloc/include",
	}
	
	filter "system:windows"
	systemversion "latest"
	
	defines
	{
		"NIRVANA_CORE_EXPORTS",
	}
	
	links
	{
		"mimalloc"
	}
	