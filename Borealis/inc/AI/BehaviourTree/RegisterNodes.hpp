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

    /*
        @brief Registers a control flow node prototype with the factory.
        @param Name The name of the control flow node class.
    */
#define REGISTER_CONTROLFLOW(Name) \
    NodeFactory::registerNodePrototype(#Name, MakeRef<Name>());

    /*
        @brief Registers a decorator node prototype with the factory.
        @param Name The name of the decorator node class.
    */
#define REGISTER_DECORATOR(Name) \
    NodeFactory::registerNodePrototype(#Name, MakeRef<Name>());

    /*
        @brief Registers a leaf node prototype with the factory.
        @param Name The name of the leaf node class.
    */
#define REGISTER_LEAF(Name) \
    NodeFactory::registerNodePrototype(#Name,  MakeRef<Name>());

    class NodeFactory
    {
    public:
        /*
            @brief Initializes the NodeFactory, registering node prototypes.
        */
        static void Init();

        /*
            @brief Registers a node prototype in the internal prototype map.
            @param nodeName The name of the node to register.
            @param prototype A reference to the node prototype.
        */
        inline static void registerNodePrototype(const std::string& nodeName, Ref<BehaviourNode> prototype) 
        { 
            nodePrototypes[nodeName] = prototype; 
        }

        /*
            @brief Creates a node by its registered name.
            @param nodeName The name of the node to create.
            @return A reference to the created node.
        */
        static Ref<BehaviourNode> createNodeByName(const std::string& nodeName);

        /*
            @brief Converts a string representation of a node type into a NodeType enum.
            @param typeStr The string representing the node type.
            @return The corresponding NodeType enum.
        */
        static NodeType string_to_node_type(const std::string& typeStr);

    private:
        /*
            @brief Recursively adds child nodes to the parent node to build the tree structure.
            @param parent The parent node.
            @param child The child node to add.
        */
        static void recursive_add(Ref<BehaviourNode> parent, Ref<BehaviourNode> child);

        /*
            @brief Finds the correct parent node based on the depth of the node.
            @param depth The depth of the node in the tree.
            @return A reference to the parent node.
        */
        static Ref<BehaviourNode> find_parent_node(int depth);

        /*
            @brief Gets the name of the current behavior tree.
            @return The name of the behavior tree.
        */
        inline static std::string get_tree_name() { return treeName; }

        /*
            @brief Sets the name of the behavior tree.
            @param name The name to set for the tree.
        */
        inline static void set_tree_name(const char* name) { treeName = name; }

        // Internal storage for registered node prototypes
        static std::unordered_map<std::string, Ref<BehaviourNode>> nodePrototypes;

        // Name of the current behavior tree
        static std::string treeName;

        // Root node of the tree
        static Ref<BehaviourNode> rootNode;

        // Tracks the most recently added node
        static Ref<BehaviourNode> previousNode;
    };
}

}

#endif
