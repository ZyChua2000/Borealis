/******************************************************************************
/*!
\file       BehaviourTree.cpp
\author     Joey Chua
\par        email: joeyjunyu.c@digipen.edu
\date       September 15, 2024
\brief      Defines the class for behaviour tree

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "BorealisPCH.hpp"
#include "AI/BehaviourTree/BehaviourNode.hpp"
#include "AI/BehaviourTree/BehaviourTree.hpp"
#include "Core/LoggerSystem.hpp"
namespace Borealis
{
    BehaviourTree::BehaviourTree() : rootNode(nullptr), treeName("")
    {}
    BehaviourTree::~BehaviourTree(){}
    void BehaviourTree::update(float dt)
    {
        rootNode->tick(dt);

        // if the root node is complete in any way, restart it
        if (rootNode->is_running() == false)
        {
            rootNode->set_status(NodeStatus::READY);
        }
    }
    void BehaviourTree::AddNode(Ref<BehaviourNode> parent, Ref<BehaviourNode> child, int depth)
    {
        if (depth == 0) {
            // The root node is being added at depth 0
            if (!rootNode) {
                rootNode = child;  // If no root node exists, make the child the root
                rootNode->set_depth(0);  // Set depth for root node
                previousNode = rootNode;  // Set previousNode to rootNode after it is added
            }
            else {
                BOREALIS_CORE_ERROR("Error: Root node already exists!");
            }
        }
        else {
            if (!parent) {
                // If no parent is provided, assume we're continuing from the last added node
                parent = previousNode;
            }

            if (!parent) {
                BOREALIS_CORE_ERROR("Error: No valid parent for depth {0}.", depth);
                return;
            }

            if (depth > parent->get_depth()) {
                // Add child to the parent if the depth is greater than the parent's depth
                child->set_depth(depth);
                parent->add_child(child);
                previousNode = child;  // Update previousNode to the newly added child
            }
            else {
                // Traverse up the tree to find the appropriate parent for the current depth
                Ref<BehaviourNode> current = parent;
                while (current->get_depth() >= depth) {
                    // Safely convert weak_ptr to shared_ptr using lock()
                    auto parentPtr = current->get_parent().lock();  // Convert weak_ptr to shared_ptr
                    if (!parentPtr) {
                        BOREALIS_CORE_ERROR("Error: Parent node is no longer valid.");
                        return;
                    }
                    current = parentPtr;  // Update current to the parent
                }

                // Add child to the appropriate parent node
                child->set_depth(depth);
                current->add_child(child);
                previousNode = child;  // Update previousNode to the newly added child
            }
        }
    }
    void BehaviourTree::SetRootNode(Ref<BehaviourNode> root)
    {
        root->set_depth(0);
        rootNode = root;
    } 
    Ref<BehaviourNode> BehaviourTree::GetRootNode() 
    {
        return rootNode;
    }
    void BehaviourTree::SetBehaviourTreeName(std::string&& name)
    {
        treeName = name;
        BOREALIS_CORE_TRACE("Name of tree set to {}",treeName);

    }
    void BehaviourTree::SetBehaviourTreeName(std::string& name)
    {
        treeName = name;
        BOREALIS_CORE_TRACE("Name of tree set to {}", treeName);

    }
    std::string BehaviourTree::GetBehaviourTreeName() const
    {
        return treeName;
    }
}