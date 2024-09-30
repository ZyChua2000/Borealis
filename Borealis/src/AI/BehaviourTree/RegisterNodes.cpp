/******************************************************************************
/*!
\file       RegisterNodes.hpp
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
            return it->second->clone();  // Clone the prototype to get a new instance
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
    void NodeFactory::build_tree_from_file(const std::string& filename, Entity ent)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            BOREALIS_CORE_ERROR("Error: Could not open file {}!", filename);
            return;
        }

        std::vector<Ref<BehaviourNode>> nodeByDepth;  // To manage nodes by depth
        Ref<BehaviourNode> root = nullptr;
        std::string line;

        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string keyword;
            iss >> keyword;

            if (keyword == "TREENAME")
            {
                std::string treeName;
                iss >> treeName;
                BOREALIS_CORE_INFO("Building Tree: {0}", treeName);
            }
            else if (keyword == "TREENODE")
            {
                std::string nodeTypeStr;
                int depth;
                iss >> nodeTypeStr >> depth;

                // Create the node using the node name
                Ref<BehaviourNode> newNode = createNodeByName(nodeTypeStr);
                if (!newNode)
                {
                    BOREALIS_CORE_ERROR("Error: Failed to create node of type {0}", nodeTypeStr);
                    continue;
                }

                // Ensure that nodeByDepth has enough space to hold the current depth
                if (depth >= nodeByDepth.size())
                {
                    nodeByDepth.resize(depth + 1, nullptr);  // Resize to fit the current depth
                }

                if (depth == 0)
                {
                    // The first node at depth 0 is the root node
                    root = newNode;
                }
                else
                {
                    // Attach this node to its parent at depth - 1
                    if (nodeByDepth[depth - 1])
                    {
                        nodeByDepth[depth - 1]->add_child(newNode);
                    }
                    else
                    {
                        BOREALIS_CORE_ERROR("Error: No valid parent node found for depth {0}", depth);
                    }
                }

                // Store the current node at its depth in the vector
                nodeByDepth[depth] = newNode;
            }
        }

        file.close();

        // Check if root node was created
        if (!root)
        {
            BOREALIS_CORE_ERROR("Error: Tree root not found.");
            return;
        }

        // Properly initialize the BehaviourTree
        Ref<BehaviourTree> treeContainer = std::make_shared<BehaviourTree>();
        treeContainer->SetRootNode(root);

        // Ensure the entity has the BehaviourTreeComponent before adding the tree
        if (!ent.HasComponent<BehaviourTreeComponent>()) {
            BOREALIS_CORE_ERROR("Error: Entity does not have a BehaviourTreeComponent.");
            return;
        }

        ent.GetComponent<BehaviourTreeComponent>().AddTree(treeContainer);
    }
}

