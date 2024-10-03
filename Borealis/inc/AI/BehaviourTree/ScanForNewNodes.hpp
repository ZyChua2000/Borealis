/******************************************************************************
/*!
\file       ScanForNewNodes.hpp
\author     Joey Chua
\par        email: joeyjunyu.c@digipen.edu
\date       September 15, 2024
\brief      Declares class for scanning new nodes added, still a WIP and may be removed

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ScanForNewNodes_HPP
#define ScanForNewNodes_HPP
#include <filesystem>
#include <iostream>
#include <fstream>
#include <set>
#include <regex>

namespace Borealis
{

	// Function to scan files and get node names
	std::set<std::string> ScanForNodes(const std::string& directory, const std::string& type);

	// Function to check if a node is already registered
	bool IsNodeRegistered(const std::string& node, const std::set<std::string>& registeredNodes);

	// Function to read registered nodes from NodesDef.hpp
	std::set<std::string> GetRegisteredNodes(const std::string& filePath);

	// Function to update NodesDef.hpp with new nodes
	void UpdateNodesDef(const std::string& filePath);



}

#endif
