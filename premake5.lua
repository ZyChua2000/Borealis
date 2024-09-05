
workspace "Borealis"
	architecture "x64"

	startproject "BorealisEditor"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLFW"] = "Borealis/lib/GLFW/include"
	IncludeDir["GLAD"] = "Borealis/lib/GLAD/include"
	IncludeDir["ImGui"] = "Borealis/lib/imgui"
	IncludeDir["GLM"] = "Borealis/lib/glm"
	IncludeDir["STBI"] = "Borealis/lib/stb_image"
	IncludeDir["ENTT"] = "Borealis/lib/ENTT/include"
	IncludeDir["YAML"] = "Borealis/lib/yaml-cpp/include"
	IncludeDir["ImGuizmo"] = "Borealis/lib/ImGuizmo"
	IncludeDir["assimp"] = "Borealis/lib/assimp/include"
	IncludeDir["FMOD"] = "Borealis/lib/FMOD"

	group "Dependencies"
		include "Borealis/lib/GLFW"
		include "Borealis/lib/GLAD"
		include "Borealis/lib/ImGui"
		include "Borealis/lib/yaml-cpp"
		include "Borealis/lib/assimp"
	group ""

	project "Borealis"
		location "Borealis"
		kind "StaticLib"
		language "C++"
		cppdialect "C++20"
		staticruntime "off"
		systemversion "latest"

		targetdir ("build/" .. outputdir .. "/%{prj.name}")
		objdir ("build-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/**.hpp",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/lib/stb_image/**.h",
			"%{prj.name}/lib/stb_image/**.cpp",
			"%{prj.name}/lib/glm/glm/**.hpp",
			"%{prj.name}/lib/glm/glm/**.inl",
			"%{prj.name}/lib/imGuizmo/imGuizmo.h",
			"%{prj.name}/lib/imGuizmo/imGuizmo.cpp"
		}

		defines
		{
			"_CRT_SECURE_NO_WARNINGS",
			"YAML_CPP_STATIC_DEFINE"
		}

		includedirs
		{
			"%{prj.name}/inc",
			"%{prj.name}/lib/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLAD}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.GLM}",
			"%{IncludeDir.STBI}",
			"%{IncludeDir.ENTT}",
			"%{IncludeDir.YAML}",
			"%{IncludeDir.ImGuizmo}",
			"%{IncludeDir.assimp}",
			"%{IncludeDir.FMOD}"
		}

		libdirs 
		{
			"Borealis/lib/FMOD/lib"
		}

		links
		{
			"GLFW",
			"GLAD",
			"ImGui",
			"yaml-cpp",
			"opengl32.lib",
			"Assimp"
		}


		defines
		{
			"BOREALIS_BUILD_DLL",
			"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
			"GLFW_INCLUDE_NONE"
		}

		pchheader "BorealisPCH.hpp"
		pchsource "Borealis/src/BorealisPCH.cpp"

		filter "files:Borealis/lib/ImGuizmo/**.cpp"
		flags {"NoPCH"}

		filter "configurations:Debug"
			defines "_DEB"
			symbols "On"
			runtime "Debug"
			links
			{
				"fmodL_vc.lib",
				"fmodstudioL_vc.lib"
			}

		filter "configurations:Release"
			defines "_REL"
			optimize "On"
			runtime "Release"
			links
			{
				"fmod_vc.lib",
				"fmodstudio_vc.lib"
			}

		filter "configurations:Distribution"
			defines "_DIST"
			optimize "On"
			runtime "Release"
			links
			{
				"fmod_vc.lib",
				"fmodstudio_vc.lib"
			}

	project "BorealisEditor"
		location "BorealisEditor"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++20"
		staticruntime "off"
		systemversion "latest"

		targetdir ("build/" .. outputdir .. "/%{prj.name}")
		objdir ("build-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/inc/**.hpp",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Borealis",
			"Borealis/inc",
			"Borealis/lib/spdlog/include",
			"%{IncludeDir.GLM}",
			"%{IncludeDir.ImGui}",
			"%{prj.name}/inc",
			"%{IncludeDir.ENTT}",
			"%{IncludeDir.ImGuizmo}"
		}

		defines
		{
			"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
		}

		links
		{
			"Borealis"
		}

		linkoptions
		{
			"/NODEFAULTLIB:library"
		}

		filter "configurations:Debug"
			defines "_DEB"
			symbols "On"
			runtime "Debug"
			postbuildcommands {
				"{COPYFILE} \"../Borealis/lib/FMOD/dll/fmodL.dll\" $(TargetDir)",
				"{COPYFILE} \"../Borealis/lib/FMOD/dll/fmodstudioL.dll\" $(TargetDir)"
			 }

		filter "configurations:Release"
			defines "_REL"
			optimize "On"
			runtime "Release"
			postbuildcommands {
				"{COPYFILE} \"../Borealis/lib/FMOD/dll/fmod.dll\" $(TargetDir)",
				"{COPYFILE} \"../Borealis/lib/FMOD/dll/fmodstudio.dll\" $(TargetDir)"
			 }

		filter "configurations:Distribution"
			defines "_DIST"
			optimize "On"
			runtime "Release"
			postbuildcommands {
				"{COPYFILE} \"../Borealis/lib/FMOD/dll/fmod.dll\" $(TargetDir)",
				"{COPYFILE} \"../Borealis/lib/FMOD/dll/fmodstudio.dll\" $(TargetDir)"
			 }

			project "Sandbox"
			location "Sandbox"
			kind "ConsoleApp"
			language "C++"
			cppdialect "C++20"
			staticruntime "off"
			systemversion "latest"
	
			targetdir ("build/" .. outputdir .. "/%{prj.name}")
			objdir ("build-int/" .. outputdir .. "/%{prj.name}")
	
			files
			{
				"%{prj.name}/inc/**.hpp",
				"%{prj.name}/src/**.cpp"
			}
	
			includedirs
			{
				"Borealis",
				"Borealis/inc",
				"Borealis/lib/spdlog/include",
				"%{IncludeDir.GLM}",
				"%{IncludeDir.ImGui}",
				"%{prj.name}/inc",
				"%{IncludeDir.ENTT}"
			}
	
			defines
			{
				"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
			}
	
			links
			{
				"Borealis"
			}
			
			linkoptions
			{
				"/NODEFAULTLIB:library"
			}
			
			filter "configurations:Debug"
				defines "_DEB"
				symbols "On"
				runtime "Debug"
	
			filter "configurations:Release"
				defines "_REL"
				optimize "On"
				runtime "Release"
	
			filter "configurations:Distribution"
				defines "_DIST"
				optimize "On"
				runtime "Release"