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

	/*!***********************************************************************
		\brief
			Function to scan files and get node names
		\param[in] directory
			The directory to scan
		\param[in] type
			The type of node to scan for
	*************************************************************************/
	std::set<std::string> ScanForNodes(const std::string& directory, const std::string& type);

	/*!***********************************************************************
		\brief
			Function to check if a node is already registered
		\param[in] node
			The name of the node to check
		\param[in] registeredNodes
			The list of registered nodes
		\return
			True if the node is already registered, false otherwise
	*************************************************************************/
	bool IsNodeRegistered(const std::string& node, const std::set<std::string>& registeredNodes);

	/*!***********************************************************************
		\brief
			Function to read registered nodes from NodesDef.hpp
		\param[in] filepath
			The path to NodesDef.hpp
		\return
			The set of registered nodes names
	*************************************************************************/
	std::set<std::string> GetRegisteredNodes(const std::string& filePath);

	/*!***********************************************************************
		\brief
			Function to update registered nodes from NodesDef.hpp
		\param[in] filepath
			The path to NodesDef.hpp
	*************************************************************************/
	void UpdateNodesDef(const std::string& filePath);
}

#endif
