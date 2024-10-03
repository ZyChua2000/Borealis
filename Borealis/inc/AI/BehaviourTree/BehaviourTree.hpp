/******************************************************************************
/*!
\file       BehaviourTree.hpp
\author     Joey Chua
\par        email: joeyjunyu.c@digipen.edu
\date       September 15, 2024
\brief      Declares the class for behaviour tree
Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef BEHAVIOURTREE_HPP
#define BEHAVIOURTREE_HPP

#include <Core/Core.hpp>
#include <string>
namespace Borealis
{
    // Forward declaration
    class BehaviourNode;

    class BehaviourTree
    {
    public:
        BehaviourTree();
        ~BehaviourTree();

        /*
            @brief Adds a child node to the given parent node.
            @param parent The parent node to which the child will be added.
            @param child The child node to add.
            @param depth The depth of the child node.
        */
        void AddNode(Ref<BehaviourNode> parent, Ref<BehaviourNode> child, int depth);

        /*
            @brief Sets the root node of the behavior tree.
            @param root The root node to be set.
        */
        void SetRootNode(Ref<BehaviourNode> root);

        /*
            @brief Retrieves the root node of the behavior tree.
            @return A reference to the root node.
        */
        Ref<BehaviourNode> GetRootNode();

        /*
            @brief Updates the behavior tree by calling the update function on the root node.
            @param dt Delta time for updating the nodes.
        */
        void update(float dt);

        /*
            @brief Sets the name of the behavior tree using an rvalue reference.
            @param name The name to set (rvalue).
        */
        void SetBehaviourTreeName(std::string&& name);

        /*
            @brief Sets the name of the behavior tree using an lvalue reference.
            @param name The name to set (lvalue).
        */
        void SetBehaviourTreeName(std::string& name);

        /*
            @brief Retrieves the name of the behavior tree.
            @return The name of the tree as a string.
        */
        std::string GetBehaviourTreeName() const;

    private:
        Ref<BehaviourNode> rootNode;  // The root node of the behavior tree
        Ref<BehaviourNode> previousNode;  // Keeps track of the previously added node
        std::string treeName;  // Name of the behavior tree
    };
}
