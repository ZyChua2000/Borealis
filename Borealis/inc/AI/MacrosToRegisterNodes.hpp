/******************************************************************************
/*!
\file       MacrosToRegisterNodes.hpp
\author     Joey Chua
\par        email: joeyjunyu.c@digipen.edu
\date       September 15, 2024
\brief      Declares

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef MacrosToRegisterNodes_HPP
#define MacrosToRegisterNodes_HPP
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "AI/BehaviourNode.hpp"
#include "Scene\Entity.hpp"
namespace Borealis
{
    class NodeFactory
    {
    private:
        // Recursive function to build the tree from the added nodes
        void recursive_add(Ref<BehaviourNode> parent, Ref<BehaviourNode> child)
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

        // Tree root node
        Ref<BehaviourNode> rootNode;

        // Tracks the most recently added node for managing hierarchy
        Ref<BehaviourNode> previousNode;

        // Name of the behavior tree
        std::string treeName;

        // Function to find the correct parent node based on depth
        Ref<BehaviourNode> find_parent_node(int depth)
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

        std::string get_tree_name()
        {
            return treeName;
        }

        void set_tree_name(const char* name)
        {
            treeName = name;
        }
    public:
        NodeFactory() : rootNode(nullptr), previousNode(nullptr), treeName("")
        {
        }
        // Map to store prototypes
        std::unordered_map<std::string, Ref<BehaviourNode>> nodePrototypes;

        // Function to register a node prototype in the map
        void registerNodePrototype(const std::string& nodeName, Ref<BehaviourNode> prototype) 
        {
            nodePrototypes[nodeName] = prototype;
        }

        // Macro definitions to register nodes dynamically
#define REGISTER_CONTROLFLOW(Name) \
    registerNodePrototype(#Name, std::make_shared Name());

#define REGISTER_DECORATOR(Name) \
    registerNodePrototype(#Name, new Name());

#define REGISTER_LEAF(Name) \
    registerNodePrototype(#Name, new Name());

// Function to initialize and register all nodes from Nodes.def
        void initializeNodePrototypes() {
            //#include "Nodes.def"  // Include the definition file
        }

        // Function to create a node by name
        Ref<BehaviourNode> createNodeByName(const std::string& nodeName) 
        {
            auto it = nodePrototypes.find(nodeName);
            if (it != nodePrototypes.end()) 
            {
                return it->second->clone();  // Clone the prototype to get a new instance
            }
            else 
            {
                std::cerr << "Error: Node type " << nodeName << " not found!" << std::endl;
                return nullptr;
            }
        }
        NodeType string_to_node_type(const std::string& typeStr)
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
        // Parse the behavior tree file and build the tree for the entity
        void build_tree_from_file(const std::string& filename, Entity ent)
        {
            std::ifstream file(filename);
            if (!file.is_open())
            {
                std::cerr << "Error: Could not open file " << filename << std::endl;
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
                    std::cout << "Building Tree: " << treeName << std::endl;
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
                        std::cerr << "Error: Failed to create node of type " << nodeTypeStr << std::endl;
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
                            std::cerr << "Error: No valid parent node found for depth " << depth << std::endl;
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
                std::cerr << "Error: Tree root not found." << std::endl;
                return;
            }

            // Properly initialize the BehaviourTree
            Ref<BehaviourTree> treeContainer = std::make_shared<BehaviourTree>();
            treeContainer->SetRootNode(root);

            // Ensure the entity has the BehaviourTreeComponent before adding the tree
            if (!ent.HasComponent<BehaviourTreeComponent>()) {
                std::cerr << "Error: Entity does not have a BehaviourTreeComponent." << std::endl;
                return;
            }

            ent.GetComponent<BehaviourTreeComponent>().AddTree(treeContainer);
        }



    };
}

#endif
