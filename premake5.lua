
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
	IncludeDir["ENTT"] = "Borealis/lib/ENTT/include"
	IncludeDir["YAML"] = "Borealis/lib/yaml-cpp/include"
	IncludeDir["ImGuizmo"] = "Borealis/lib/ImGuizmo"
	IncludeDir["FMOD"] = "Borealis/lib/FMOD"
	IncludeDir["Tracy"] = "Borealis/lib/tracy"
	IncludeDir["STBI"] = "Borealis/lib/stb_image"
	IncludeDir["JoltPhysics"] = "Borealis/lib/JoltPhysics"
	IncludeDir["Mono"] = "Borealis/lib/mono/include"
	IncludeDir["xproperty"] = "Borealis/lib/xproperty/include"

	IncludeDir["assimp"] = "BorealisEditor/lib/assimp/include"
	IncludeDir["ImGuiNodeEditor"] = "BorealisEditor/lib/imgui-node-editor"
	IncludeDir["MSDF"] = "BorealisEditor/lib/MSDF/Include"

	LibraryDir = {}
	LibraryDir["FMOD"] = "lib/FMOD/lib"
	LibraryDir["Mono_Debug"] = "lib/mono/lib/Deb"
	LibraryDir["Mono_Release"] = "lib/mono/lib/Rel"
	LibraryDir["MSDF_Debug"] = "lib/MSDF/Build/Debug"
	LibraryDir["MSDF_Release"] = "lib/MSDF/Build/Release"

	Library = {}
	Library["FMOD_Debug"] = "%{LibraryDir.FMOD}/fmodL_vc.lib"
	Library["FMOD_Release"] = "%{LibraryDir.FMOD}/fmod_vc.lib"
	Library["Mono_Debug"] = "%{LibraryDir.Mono_Debug}/mono-2.0-sgen.lib"
	Library["Mono_Release"] = "%{LibraryDir.Mono_Release}/mono-2.0-sgen.lib"

	Library["MSDF_Debug_atlas"] = "%{LibraryDir.MSDF_Debug}/msdf-atlas-gen.lib"
	Library["MSDF_Debug_core"] = "%{LibraryDir.MSDF_Debug}/msdfgen-core.lib"
	Library["MSDF_Debug_ext"] = "%{LibraryDir.MSDF_Debug}/msdfgen-ext.lib"
	Library["MSDF_Debug_FreeType"] = "%{LibraryDir.MSDF_Debug}/freetyped.lib"
	Library["MSDF_Debug_LibPNG"] = "%{LibraryDir.MSDF_Debug}/libpng16d.lib"

	Library["MSDF_Release_atlas"] = "%{LibraryDir.MSDF_Release}/msdf-atlas-gen.lib"
	Library["MSDF_Release_core"] = "%{LibraryDir.MSDF_Release}/msdfgen-core.lib"
	Library["MSDF_Release_ext"] = "%{LibraryDir.MSDF_Release}/msdfgen-ext.lib"
	Library["MSDF_Release_FreeType"] = "%{LibraryDir.MSDF_Release}/freetype.lib"
	Library["MSDF_Release_LibPNG"] = "%{LibraryDir.MSDF_Release}/libpng16.lib"

	group "Dependencies"
		include "Borealis/lib/GLFW"
		include "Borealis/lib/GLAD"
		include "Borealis/lib/ImGui"
		include "Borealis/lib/yaml-cpp"
		include "Borealis/lib/Tracy"
		include "Borealis/lib/JoltPhysics"
		include "BorealisEditor/lib/assimp"
		include "BorealisEditor/lib/imgui-node-editor"
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
			"%{prj.name}/lib/glm/glm/**.hpp",
			"%{prj.name}/lib/glm/glm/**.inl",
			"%{prj.name}/lib/imGuizmo/imGuizmo.h",
			"%{prj.name}/lib/imGuizmo/imGuizmo.cpp",
			"%{prj.name}/lib/stb_image/**.h",
			"%{prj.name}/lib/stb_image/**.cpp"
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
			"%{IncludeDir.ENTT}",
			"%{IncludeDir.YAML}",
			"%{IncludeDir.ImGuizmo}",
			"%{IncludeDir.FMOD}",
			"%{IncludeDir.Tracy}",
			"%{IncludeDir.STBI}",
			"%{IncludeDir.JoltPhysics}",
			"%{IncludeDir.Mono}",
			"%{IncludeDir.xproperty}"
		}


		links
		{
			"GLFW",
			"GLAD",
			"ImGui",
			"yaml-cpp",
			"opengl32.lib",
			"Tracy",
			"JoltPhysics"
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
				"%{Library.FMOD_Debug}",
				"%{Library.Mono_Debug}"
			}

		filter "configurations:Release"
			defines "_REL"
			optimize "On"
			runtime "Release"
			links
			{
				"%{Library.FMOD_Release}",
				"%{Library.Mono_Release}"
			}

		filter "configurations:Distribution"
			defines "_DIST"
			optimize "On"
			runtime "Release"
			links
			{
				"%{Library.FMOD_Release}",
				"%{Library.Mono_Release}"
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
			"%{IncludeDir.YAML}",
			"%{IncludeDir.GLM}",
			"%{IncludeDir.ImGui}",
			"%{prj.name}/inc",
			"%{IncludeDir.ENTT}",
			"%{IncludeDir.ImGuizmo}",
			"%{IncludeDir.ImGuiNodeEditor}",
			"%{IncludeDir.assimp}",
			"%{IncludeDir.MSDF}",
		}

		defines
		{
			"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
			"YAML_CPP_STATIC_DEFINE"
		}

		links
		{
			"Borealis",
			"Assimp",
			"yaml-cpp",
			"ImGuiNodeEditor",
			"BorealisScriptCore"
		}

		linkoptions
		{
			"/NODEFAULTLIB:LIBCMTD"
		}

		filter "configurations:Debug"
			defines "_DEB"
			symbols "On"
			runtime "Debug"
			postbuildcommands {
				"{COPYFILE} \"../Borealis/lib/FMOD/dll/fmodL.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../Borealis/lib/mono/dll/Deb/mono-2.0-sgen.dll\" \"$(TargetDir)\"",

				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Debug/dll/brotlicommon.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Debug/dll/brotlidec.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Debug/dll/bz2d.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Debug/dll/libpng16d.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Debug/dll/freetyped.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Debug/dll/zlibd1.dll\" \"$(TargetDir)\""
			 }
			links
			{
				"%{Library.MSDF_Debug_atlas}",
				"%{Library.MSDF_Debug_core}",
				"%{Library.MSDF_Debug_ext}",
				"%{Library.MSDF_Debug_FreeType}",
				"%{Library.MSDF_Debug_LibPNG}"
			}

		filter "configurations:Release"
			defines "_REL"
			optimize "On"
			runtime "Release"
			postbuildcommands {
				"{COPYFILE} \"../Borealis/lib/FMOD/dll/fmod.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../Borealis/lib/mono/dll/Rel/mono-2.0-sgen.dll\" \"$(TargetDir)\"",

				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Release/dll/brotlicommon.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Release/dll/brotlidec.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Release/dll/bz2d.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Release/dll/libpng16d.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Release/dll/freetyped.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Release/dll/zlibd1.dll\" \"$(TargetDir)\""
			 }
			 links
			{
				"%{Library.MSDF_Release_atlas}",
				"%{Library.MSDF_Release_core}",
				"%{Library.MSDF_Release_ext}",
				"%{Library.MSDF_Release_FreeType}",
				"%{Library.MSDF_Release_LibPNG}"
			}

		filter "configurations:Distribution"
			defines "_DIST"
			optimize "On"
			runtime "Release"
			postbuildcommands {
				"{COPYFILE} \"../Borealis/lib/FMOD/dll/fmod.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../Borealis/lib/mono/dll/Rel/mono-2.0-sgen.dll\" \"$(TargetDir)\"",

				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Release/dll/brotlicommon.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Release/dll/brotlidec.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Release/dll/bz2d.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Release/dll/libpng16d.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Release/dll/freetyped.dll\" \"$(TargetDir)\"",
				"{COPYFILE} \"../BorealisEditor/lib/MSDF/Build/Release/dll/zlibd1.dll\" \"$(TargetDir)\""
			 }
			 links
			{
				"%{Library.MSDF_Release_atlas}",
				"%{Library.MSDF_Release_core}",
				"%{Library.MSDF_Release_ext}",
				"%{Library.MSDF_Release_FreeType}",
				"%{Library.MSDF_Release_LibPNG}"
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
				"/NODEFAULTLIB:LIBCMTD"
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

	project "BorealisScriptCore"
		location "BorealisScriptCore"
		kind "SharedLib"
		language "C#"
		dotnetframework "4.7.2"

		targetdir("BorealisEditor/Resources/Scripts/Core")
		objdir ("BorealisEditor/Resources/Scripts/Core/Intermediate")

		files
		{
			"%{prj.name}/src/**.cs",
			"%{prj.name}/props/**.cs"
		}

		links
		{
			"packages/Microsoft.CodeAnalysis.Common.4.11.0/lib/netstandard2.0/Microsoft.CodeAnalysis",
			"packages/Microsoft.CodeAnalysis.CSharp.4.11.0/lib/netstandard2.0/Microsoft.CodeAnalysis.CSharp",
			"packages/Microsoft.CodeAnalysis.Analyzers.3.3.4/analyzers/dotnet/cs/Microsoft.CodeAnalysis.Analyzers",
			"packages/Microsoft.CodeAnalysis.Analyzers.3.3.4/analyzers/dotnet/cs/Microsoft.CodeAnalysis.CSharp.Analyzers",
			"System.Buffers",
			"System.Collections.Immutable",
			"System.Memory",
			"System.Reflection.Metadata",
			"System.Runtime.CompilerServices.Unsafe"
		}

		filter "configurations:Debug"
			optimize "Off"
			symbols "Default"

		filter "configurations:Release"
			optimize "On"
			symbols "Default"

		filter "configurations:Distribution"
			optimize "Full"
			symbols "Off"