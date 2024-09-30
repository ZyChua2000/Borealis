/******************************************************************************
/*!
\file       RegisterNodes.hpp
\author     Joey Chua
\par        email: joeyjunyu.c@digipen.edu
\date       September 15, 2024
\brief      Declares the class for node factory

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef REGISTER_NODES_HPP
#define REGISTER_NODES_HPP
#include <unordered_map>
#include <string>
#include "AI/BehaviourTree/BehaviourNode.hpp"
#include "Scene\Entity.hpp"
namespace Borealis
{

    // Macro definitions to register nodes dynamically
#define REGISTER_CONTROLFLOW(Name) \
    NodeFactory::registerNodePrototype(#Name, MakeRef<Name>());

#define REGISTER_DECORATOR(Name) \
    NodeFactory::registerNodePrototype(#Name, MakeRef<Name>());

#define REGISTER_LEAF(Name) \
    NodeFactory::registerNodePrototype(#Name,  MakeRef<Name>());

    class NodeFactory
    {
    public:
        static void Init();

        // Function to register a node prototype in the map
        inline static void registerNodePrototype(const std::string& nodeName, Ref<BehaviourNode> prototype) { nodePrototypes[nodeName] = prototype; }

// Function to initialize and register all nodes from Nodes.def
        static void initializeNodePrototypes() {
            //#include "Nodes.def"  // Include the definition file
        }

        // Function to create a node by name
        static Ref<BehaviourNode> createNodeByName(const std::string& nodeName);

        static NodeType string_to_node_type(const std::string& typeStr);

        // Parse the behavior tree file and build the tree for the entity
        static void build_tree_from_file(const std::string& filename, Entity ent);

    private:

        // Recursive function to build the tree from the added nodes
        static void recursive_add(Ref<BehaviourNode> parent, Ref<BehaviourNode> child);

        // Function to find the correct parent node based on depth
        static Ref<BehaviourNode> find_parent_node(int depth);

        inline static std::string get_tree_name() { return treeName; }

        inline static void set_tree_name(const char* name) { treeName = name; }

        // Map to store prototypes
        static std::unordered_map<std::string, Ref<BehaviourNode>> nodePrototypes;

        // Name of the behavior tree
        static std::string treeName;

        // Tree root node
        static Ref<BehaviourNode> rootNode;

        // Tracks the most recently added node for managing hierarchy
        static Ref<BehaviourNode> previousNode;



    };
}

#endif
