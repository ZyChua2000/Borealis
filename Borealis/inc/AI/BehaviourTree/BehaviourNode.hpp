/******************************************************************************
/*!
\file       BehaviurNode.hpp
\author     Joey Chua
\par        email: joeyjunyu.c@digipen.edu
\date       September 15, 2024
\brief      Declares the class for behaviour node, NodeType, NodeResult and NodeStatus

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef BEHAVIOURNODE_HPP
#define BEHAVIOURNODE_HPP

#include <Core/Core.hpp>
#include <string>
#include <memory>
#include <vector>
namespace Borealis
{
    class Serialiser;
    enum class NodeType
    {
        CONTROLFLOW,
        DECORATOR,
        LEAF,
        UNKNOWN
    };

    enum class NodeStatus
    {
        READY, // node is enterable
        RUNNING, // node is currently running
        EXITING, // node has succeeded or failed
        SUSPENDED // node won't exceute anything
    };

    enum class NodeResult
    {
        IN_PROGRESS, // still being run 
        SUCCESS, // node succeeded
        FAILURE // node failed
    };

 class BehaviourNode : public std::enable_shared_from_this<BehaviourNode>
{
    friend class NodeFactory;
    friend class Serialiser;

public:
    BehaviourNode() = default;

    /*
        @brief Gets the type of the node.
        @return The NodeType of the node.
    */
    NodeType get_type() const;

    /*
        @brief Sets the depth of the node in the behavior tree.
        @param depth The depth to set.
    */
    void set_depth(int depth);

    /*
        @brief Gets the depth of the node in the behavior tree.
        @return The depth as an integer.
    */
    int get_depth() const;

    /*
        @brief Gets the name of the node.
        @return The node's name as a string.
    */
    std::string get_name() const;

    /*
        @brief Retrieves the parent node.
        @return A weak reference to the parent node.
    */
    WeakRef<BehaviourNode> get_parent() const;

    /*
        @brief Sets the name of the node.
        @param setName The name to set.
    */
    void set_name(const std::string& setName);

    /*
        @brief Adds a child node to this node.
        @param child The BehaviourNode to add as a child.
    */
    void add_child(Ref<BehaviourNode> child);

    /*
        @brief Checks if the node is in the READY state.
        @return True if the node is READY, false otherwise.
    */
    bool is_ready() const;

    /*
        @brief Checks if the node has succeeded.
        @return True if the node's result is SUCCESS, false otherwise.
    */
    bool succeeded() const;

    /*
        @brief Checks if the node has failed.
        @return True if the node's result is FAILURE, false otherwise.
    */
    bool failed() const;

    /*
        @brief Checks if the node is currently running.
        @return True if the node is RUNNING, false otherwise.
    */
    bool is_running() const;

    /*
        @brief Checks if the node is suspended.
        @return True if the node is SUSPENDED, false otherwise.
    */
    bool is_suspended() const;

    /*
        @brief Sets the status of this node.
        @param newStatus The status to set.
    */
    void set_status(NodeStatus newStatus);

    /*
        @brief Recursively sets the status for this node and all of its children.
        @param newStatus The status to set for the node and its children.
    */
    void set_status_all(NodeStatus newStatus);

    /*
        @brief Sets the status for all the node's immediate children.
        @param newStatus The status to set for the children.
    */
    void set_status_children(NodeStatus newStatus);

    /*
        @brief Sets the result for this node.
        @param result The result to set.
    */
    void set_result(NodeResult result);

    /*
        @brief Sets the result for all the node's children.
        @param result The result to set for the children.
    */
    void set_result_children(NodeResult result);

    /*
        @brief Gets the current status of the node.
        @return The node's status.
    */
    NodeStatus get_status() const;

    /*
        @brief Gets the result of the node.
        @return The node's result.
    */
    NodeResult get_result() const;

    /*
        @brief Updates the node's state based on its status.
        @param dt The delta time for updating the node.
    */
    void tick(float dt);

    /*
        @brief Clones the node to create a new instance of the same type.
        @return A shared reference to the cloned node.
    */
    virtual Ref<BehaviourNode> clone() = 0;

protected:
    /*
        @brief Called when a leaf node starts execution.
    */
    void on_leaf_enter();

    /*
        @brief Called when the node enters execution.
    */
    virtual void on_enter();

    /*
        @brief Called when the node is updated.
        @param dt The delta time for updating the node.
    */
    virtual void on_update(float dt);

    /*
        @brief Called when the node exits execution.
    */
    virtual void on_exit();

    /*
        @brief Marks the node as successful and exits execution.
    */
    void on_success();

    /*
        @brief Marks the node as failed and exits execution.
    */
    void on_failure();

private:
    int mDepth;  // Depth of the node in the behavior tree

    // Node type, status, and result
    NodeType nodeType;
    NodeStatus status;
    NodeResult result;

    WeakRef<BehaviourNode> parent;  // Parent node reference
    std::vector<Ref<BehaviourNode>> children;  // Child nodes
    std::string name;  // Name of the node
};

// Simple CRTP intermediary for cloning derived types
template <typename T>
class BaseNode : public BehaviourNode
{
public:
    /*
        @brief Clones the node to create a new instance of the derived type.
        @return A shared reference to the cloned node.
    */
    virtual Ref<BehaviourNode> clone()
    {
        return std::make_shared<T>(static_cast<const T&>(*this));
    }
};

}
