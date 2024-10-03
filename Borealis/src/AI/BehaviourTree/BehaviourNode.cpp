/******************************************************************************
/*!
\file       BehaviourNode.cpp
\author     Joey Chua
\par        email: joeyjunyu.c@digipen.edu
\date       September 15, 2024
\brief      Defines the class for behaviour node

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "BorealisPCH.hpp"
#include "AI/BehaviourTree/BehaviourNode.hpp"
#include "AI/BehaviourTree/BehaviourTree.hpp"
#include <Core/LoggerSystem.hpp>

namespace Borealis
{

    /*
        @brief Retrieves the node type (e.g., control flow, leaf, etc.).
        @return The NodeType of the node.
    */
    NodeType BehaviourNode::get_type() const
    {
        return nodeType;
    }

    /*
        @brief Retrieves the depth of the node in the behavior tree.
        @return The depth as an integer.
    */
    int BehaviourNode::get_depth() const
    {
        return mDepth;
    }

    /*
        @brief Retrieves the parent node.
        @return A weak reference to the parent BehaviourNode.
    */
    WeakRef<BehaviourNode> BehaviourNode::get_parent() const
    {
        return parent;
    }

    /*
        @brief Sets the depth of the node.
        @param depth The depth to be set.
    */
    void BehaviourNode::set_depth(int depth) 
    {
        mDepth = depth;
    }

    /*
        @brief Retrieves the name of the node.
        @return The name of the node as a string.
    */
    std::string BehaviourNode::get_name() const
    {
        return name;
    }

    /*
        @brief Sets the name of the node.
        @param setName The name to be assigned to the node.
    */
    void BehaviourNode::set_name(const std::string& setName)
    {
        name = setName;
        BOREALIS_CORE_TRACE("Name of node set to {}", name);
    }

    /*
        @brief Adds a child node to the current node.
        @param child The BehaviourNode to add as a child.
    */
    void BehaviourNode::add_child(Ref<BehaviourNode> child)
    {
        children.emplace_back(child);
        child->parent = shared_from_this();
    }

    /*
        @brief Checks if the node is in the READY state.
        @return True if the node is READY, otherwise false.
    */
    bool BehaviourNode::is_ready() const
    {
        return status == NodeStatus::READY;
    }

    /*
        @brief Checks if the node succeeded.
        @return True if the node's result is SUCCESS, otherwise false.
    */
    bool BehaviourNode::succeeded() const
    {
        return result == NodeResult::SUCCESS;
    }

    /*
        @brief Checks if the node failed.
        @return True if the node's result is FAILURE, otherwise false.
    */
    bool BehaviourNode::failed() const
    {
        return result == NodeResult::FAILURE;
    }

    /*
        @brief Checks if the node is currently running.
        @return True if the node is RUNNING, otherwise false.
    */
    bool BehaviourNode::is_running() const
    {
        return status == NodeStatus::RUNNING;
    }

    /*
        @brief Checks if the node is suspended.
        @return True if the node is SUSPENDED, otherwise false.
    */
    bool BehaviourNode::is_suspended() const
    {
        return status == NodeStatus::SUSPENDED;
    }

    /*
        @brief Sets the node's status.
        @param newStatus The new status to set.
    */
    void BehaviourNode::set_status(NodeStatus newStatus)
    {
        status = newStatus;
    }

    /*
        @brief Recursively sets the status for the node and all of its children.
        @param newStatus The new status to set for the node and its children.
    */
    void BehaviourNode::set_status_all(NodeStatus newStatus)
    {
        status = newStatus;
        for (auto&& child : children)
        {
            child->set_status_all(newStatus);
        }
    }

    /*
        @brief Sets the status of all the node's children.
        @param newStatus The new status to set for all child nodes.
    */
    void BehaviourNode::set_status_children(NodeStatus newStatus)
    {
        for (auto&& child : children)
        {
            child->set_status(newStatus);
        }
    }

    /*
        @brief Sets the result of the node.
        @param r The result to assign to the node.
    */
    void BehaviourNode::set_result(NodeResult r)
    {
        result = r;
    }

    /*
        @brief Sets the result of all the node's children.
        @param result The result to assign to all child nodes.
    */
    void BehaviourNode::set_result_children(NodeResult result)
    {
        for (auto&& child : children)
        {
            child->set_result(result);
        }
    }

    /*
        @brief Retrieves the node's current status.
        @return The node's status.
    */
    NodeStatus BehaviourNode::get_status() const
    {
        return status;
    }

    /*
        @brief Retrieves the node's result.
        @return The result of the node.
    */
    NodeResult BehaviourNode::get_result() const
    {
        return result;
    }

    /*
        @brief Updates the node based on its current status.
        @param dt The delta time for updating the node.
    */
    void BehaviourNode::tick(float dt)
    {
        if (status == NodeStatus::READY)
        {
            on_enter();
        }

        if (status == NodeStatus::RUNNING)
        {
            on_update(dt);
        }

        if (status == NodeStatus::EXITING)
        {
            on_exit();
        }
    }

    /*
        @brief Handles the logic when a node enters execution.
    */
    void BehaviourNode::on_enter()
    {
        set_status(NodeStatus::RUNNING);
        set_result(NodeResult::IN_PROGRESS);
        set_status_children(NodeStatus::READY);
        set_result_children(NodeResult::IN_PROGRESS);
    }

    /*
        @brief Handles the logic when a leaf node enters execution.
    */
    void BehaviourNode::on_leaf_enter()
    {
        set_status(NodeStatus::RUNNING);
        set_result(NodeResult::IN_PROGRESS);
    }

    /*
        @brief Handles the node's update logic.
        @param dt The delta time (not used in base logic).
    */
    void BehaviourNode::on_update(float)
    {
        // No base logic implemented
    }

    /*
        @brief Handles the logic when a node exits execution.
    */
    void BehaviourNode::on_exit()
    {
        set_status(NodeStatus::SUSPENDED);
    }

    /*
        @brief Marks the node as successful and exits execution.
    */
    void BehaviourNode::on_success()
    {
        set_status(NodeStatus::EXITING);
        set_result(NodeResult::SUCCESS);
    }

    /*
        @brief Marks the node as failed and exits execution.
    */
    void BehaviourNode::on_failure()
    {
        set_status(NodeStatus::EXITING);
        set_result(NodeResult::FAILURE);
    }


}
