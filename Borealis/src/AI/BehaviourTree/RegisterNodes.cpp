/******************************************************************************
/*!
\file       RegisterNodes.cpp
\author     Joey Chua
\par        email: joeyjunyu.c@digipen.edu
\date       September 15, 2024
\brief      Defines the class node factory

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <AI/BehaviourTree/RegisterNodes.hpp>
#include <AI/BehaviourTree/NodesDef.hpp>
#include <Core/LoggerSystem.hpp>

namespace Borealis
{
    // Map to store prototypes
    std::unordered_map<std::string, Ref<BehaviourNode>> NodeFactory::nodePrototypes;
    // Name of the behavior tree
    std::string NodeFactory::treeName;
    // Tree root node
    Ref<BehaviourNode> NodeFactory::rootNode;
    // Tracks the most recently added node for managing hierarchy
    Ref<BehaviourNode> NodeFactory::previousNode;

	void NodeFactory::recursive_add(Ref<BehaviourNode> parent, Ref<BehaviourNode> child)
	{
        // Add the child node to the parent node recursively, building the tree
        if (parent)
        {
            parent->add_child(child);

            // For each child in the current node, add them recursively
            for (auto& childNode : child->children)
            {
                recursive_add(child, childNode);
            }
        }
	}

    Ref<BehaviourNode> NodeFactory::find_parent_node(int depth)
    {
        // Find the correct parent node based on the depth
        // This could be a stack-based approach or simply walking the tree from the rootNode
        Ref<BehaviourNode> currentNode = rootNode;

        // Traverse the tree to find the node at the desired depth
        while (currentNode && currentNode->get_depth() != depth - 1)
        {
            if (!currentNode->children.empty())
            {
                currentNode = currentNode->children.back();  // Move down the tree
            }
            else
            {
                return nullptr;  // No valid parent node found at the requested depth
            }
        }

        return currentNode;
    }
    void NodeFactory::Init()
    {
        REGISTER_ALL_NODES;
    }
    Ref<BehaviourNode> NodeFactory::createNodeByName(const std::string& nodeName)
    {
        auto it = nodePrototypes.find(nodeName);
        if (it != nodePrototypes.end())
        {
            Ref<BehaviourNode> newNode = it->second->clone();
            newNode->set_name(nodeName);
            return newNode;// Clone the prototype to get a new instance
        }
        else
        {
            BOREALIS_CORE_ERROR("Error: Node type {0} not found!", nodeName);
           return nullptr;
        }
    }
    NodeType NodeFactory::string_to_node_type(const std::string& typeStr)
    {
        // Extract the first two characters
        if (typeStr.size() < 2) {
            return NodeType::UNKNOWN;
        }

        std::string prefix = typeStr.substr(0, 2);

        // Map the prefix to the appropriate node type
        if (prefix == "C_") {
            return NodeType::CONTROLFLOW;
        }
        else if (prefix == "L_") {
            return NodeType::LEAF;
        }
        else if (prefix == "D_") {
            return NodeType::DECORATOR;
        }

        return NodeType::UNKNOWN;  // Return INVALID if the prefix doesn't match any known type
    }
}

