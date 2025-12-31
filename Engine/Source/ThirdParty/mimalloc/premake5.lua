project "mimalloc"
	kind "StaticLib"
    language "C"
	
	targetdir("%{wks.location}/Binaries/NirvanaEngine/%{cfg.platform}/%{cfg.buildcfg}")
	objdir("%{wks.location}/Intermediate/NirvanaEngine/%{cfg.platform}/%{cfg.buildcfg}")
	
	files
	{
		"%{prj.location}/LICENSE",
		"src/alloc.c",
        "src/alloc-aligned.c",
        "src/alloc-posix.c",
        "src/arena.c",
        "src/bitmap.c",
        "src/heap.c",
        "src/init.c",
        "src/options.c",
        "src/os.c",
        "src/page.c",
        "src/random.c",
        "src/stats.c",
	}

	defines
    {
        "WIN32",
        "_WINDOWS",
        "MI_STATIC_LIB",
    }

	includedirs
    {
        "include",
    }

	links
    {
    }

	filter { "configurations:Debug", "configurations:DebugEditor" }
    	runtime "Debug"
    	symbols "on"
    	staticruntime "off"

	filter { "configurations:Development", "configurations:DevelopmentEditor", "configurations:Shipping" }
    	runtime "Release"
    	optimize "on"
    	staticruntime "off"
