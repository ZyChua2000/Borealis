project "GLFW"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("build/" .. outputdir .. "/%{prj.name}")
	objdir ("build-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",
        "src/glfw_config.h",
		"src/null_init.c",
		"src/null_monitor.c",
		"src/null_joystick.c",
		"src/null_window.c",
        "src/context.c",
        "src/init.c",
        "src/input.c",
        "src/monitor.c",
        "src/vulkan.c",
        "src/window.c",
		"src/platform.c"
	}


	filter "system:windows"
		systemversion "latest"

		files
		{
			"src/win32_init.c",
            "src/win32_joystick.c",
            "src/win32_monitor.c",
            "src/win32_time.c",
            "src/win32_thread.c",
            "src/win32_window.c",
			"src/win32_module.c",
            "src/wgl_context.c",
            "src/egl_context.c",
            "src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		optimize "On"
		runtime "Release"

