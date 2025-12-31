project "Premake"
	kind "Utility"

	targetdir("%{wks.location}/Binaries/Premake/%{cfg.platform}/%{cfg.buildcfg}")
	objdir("%{wks.location}/Intermediate/Premake/%{cfg.platform}/%{cfg.buildcfg}")

	files
	{
		"%{wks.location}/**premake5.lua"
	}

	postbuildmessage "Regenerating project files with Premake5..."
	postbuildcommands
	{
		"\"%{prj.location}bin/premake5\" %{_ACTION} --file=\"%{wks.location}premake5.lua\""
	}