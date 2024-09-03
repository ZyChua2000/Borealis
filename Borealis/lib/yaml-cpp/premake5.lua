project "yaml-cpp"
     kind "StaticLib"
     language "C++"
	 staticruntime "off"
	 warnings "off"

     targetdir ("build/" .. outputdir .. "/%{prj.name}")
     objdir ("build-int/" .. outputdir .. "/%{prj.name}")

     files
     {
        "src/**.h",
        "src/**.cpp",
        "include/**.h"
     }

     includedirs
     {
      "include"
     }

     defines
		{
			"yaml_cpp_EXPORTS"
		}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "speed"

    filter "configurations:Distribution"
		runtime "Release"
		optimize "speed"
        symbols "off"