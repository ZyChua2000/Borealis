/******************************************************************************/
/*!
\file		Project.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	September 09, 2024
\brief		Defines the class for the Project Management

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <Borealis.hpp>
#include <Project/Project.hpp>

namespace Borealis
{
	std::string Project::mProjectPath = "";
	std::string Project::mProjectName = "";
	void Project::CreateProject(std::string name, std::string path)
	{
		// Create Project file
		
		// Create directory if doesnt exist
		std::string projectFilePath = path;
		projectFilePath += "/";
		projectFilePath += name;

		std::filesystem::path fileSystemPaths = projectFilePath;
		std::filesystem::create_directories(fileSystemPaths);

		std::string filepath = projectFilePath;
		filepath += "/Assets";
		std::filesystem::create_directories(filepath);

		filepath = projectFilePath;
		filepath += "/Scenes";
		std::filesystem::create_directories(filepath);

		
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "ProjectName" << YAML::Value << name;

		projectFilePath += "/Project.brproj";

		std::ofstream outStream(projectFilePath);
		outStream << out.c_str();
		outStream.close();

		mProjectPath = path;
		mProjectName = name;
	}
	void Project::SetProjectPath(std::string path)
	{
		// check if project path exists
		std::string projectFile = path;
		std::string projectFilePath = projectFile.substr(0, projectFile.find_last_of("\\"));
		if (std::filesystem::exists(projectFilePath))
		{
			if (std::filesystem::exists(projectFile))
			{
				mProjectPath = projectFilePath;

				std::ifstream inStream(projectFile);
				std::stringstream ss;
				ss << inStream.rdbuf();
				inStream.close();

				YAML::Node data = YAML::Load(ss.str());
				mProjectName = data["ProjectName"].as<std::string>();
			}
			else
			{
				BOREALIS_CORE_WARN("Project file does not exist in the specified path");
			}
		}
		else
		{
			BOREALIS_CORE_WARN("Specified path does not exist");
		}
	}
	std::string Project::GetProjectPath()
	{
		return mProjectPath;
	}
	std::string Project::GetProjectName()
	{
		return mProjectName;
	}
}
