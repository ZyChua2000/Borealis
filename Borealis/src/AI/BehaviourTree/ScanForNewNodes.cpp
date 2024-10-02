/******************************************************************************
/*!
\file       ScanForNewNodes.cpp
\author     Chua Zheng Yang
\par        email: c.zhengyang@digipen.edu
\date       September 07, 2024
\brief      Defines

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include "AI/BehaviourTree/ScanForNewNodes.hpp"
#include <Core/LoggerSystem.hpp>

namespace Borealis
{
    namespace fs = std::filesystem;

    // Function to scan files and get node names
    std::set<std::string> ScanForNodes(const std::string& directory, const std::string& type) {
        std::set<std::string> nodes;
        for (const auto& entry : fs::directory_iterator(directory)) 
        {
            BOREALIS_CORE_TRACE("Found {}", entry.path().string());

            if (entry.path().extension() == ".hpp") {
                std::string filename = entry.path().stem().string(); // Get filename without extension
                nodes.insert(type + "(" + filename + ")");
            }
        }
        return nodes;
    }

    // Function to check if a node is already registered
    bool IsNodeRegistered(const std::string& node, const std::set<std::string>& registeredNodes) {
        return registeredNodes.find(node) != registeredNodes.end();
    }

    // Function to read registered nodes from NodesDef.hpp
    std::set<std::string> GetRegisteredNodes(const std::string& filePath) {
        std::set<std::string> registeredNodes;
        std::ifstream fileIn(filePath);
        std::string line;

        while (std::getline(fileIn, line)) {
            // Check if the line contains a REGISTER statement (simple string check)
            if (line.find("REGISTER_CONTROLFLOW") != std::string::npos || line.find("REGISTER_LEAF") != std::string::npos) {
                registeredNodes.insert(line); // Add the entire line as a registered node
            }
        }

        return registeredNodes;
    }

    // Function to update NodesDef.hpp with new nodes
    void UpdateNodesDef(const std::string& filePath) {
        // Read already registered nodes from NodesDef.hpp
        std::set<std::string> registeredNodes = GetRegisteredNodes(filePath);

        // Scan for new nodes in ControlFlow and Leaf directories
        auto controlFlowNodes = ScanForNodes("Borealis\inc\AI\BehaviourTree\ControlFlow", "REGISTER_CONTROLFLOW");
        auto leafNodes = ScanForNodes("Borealis\inc\AI\BehaviourTree\Leaf", "REGISTER_LEAF");

        // Open the NodesDef.hpp file for appending new nodes
        std::ofstream fileOut(filePath, std::ios_base::app);
        bool nodesAdded = false;

        // Add new ControlFlow nodes if not registered
        for (const auto& node : controlFlowNodes) {
            if (!IsNodeRegistered(node, registeredNodes)) {
                fileOut << node << " \\" << std::endl;
                nodesAdded = true;
            }
        }

        // Add new Leaf nodes if not registered
        for (const auto& node : leafNodes) {
            if (!IsNodeRegistered(node, registeredNodes)) {
                fileOut << node << " \\" << std::endl;
                nodesAdded = true;
            }
        }

        if (nodesAdded) {
            std::cout << "New nodes added to NodesDef.hpp." << std::endl;
        }
        else {
            std::cout << "No new nodes to add." << std::endl;
        }
    }
}

