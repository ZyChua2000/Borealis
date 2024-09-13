#include "BorealisPCH.hpp"
#include "AI/BehaviourNode.hpp"
#include "AI/BehaviourTree.hpp"


BehaviourNode::BehaviourNode(NodeType type, int depth, const std::string& name)
    : nodeType(type), mDepth(depth), name(name), parent(nullptr) {}

BehaviourNode::~BehaviourNode()
{
    for (auto&& child : children)
    {
        delete child;
    }

}
// Get the node type
NodeType BehaviourNode::get_type() const
{
    return nodeType;
}

// Get the depth of the node
int BehaviourNode::get_depth() const
{
    return mDepth;
}

// Get the name of the node
std::string BehaviourNode::get_name() const
{
    return name;
}

// Add a child node to this node
void BehaviourNode::add_child(BehaviourNode* child)
{
    children.emplace_back(child);
    child->parent = this;
    //child->agent = agent;
}

bool BehaviourNode::is_ready() const
{
    return status == NodeStatus::READY;
}

bool BehaviourNode::succeeded() const
{
    return result == NodeResult::SUCCESS;
}

bool BehaviourNode::failed() const
{
    return result == NodeResult::FAILURE;
}

bool BehaviourNode::is_running() const
{
    return status == NodeStatus::RUNNING;
}

bool BehaviourNode::is_suspended() const
{
    return status == NodeStatus::SUSPENDED;
}

void BehaviourNode::set_status(NodeStatus newStatus)
{
    status = newStatus;
}

void BehaviourNode::set_status_all(NodeStatus newStatus)
{
    status = newStatus;

    for (auto&& child : children)
    {
        child->set_status_all(newStatus);
    }
}

void BehaviourNode::set_status_children(NodeStatus newStatus)
{
    for (auto&& child : children)
    {
        child->set_status(newStatus);
    }
}

void BehaviourNode::set_result(NodeResult r)
{
    result = r;
}

void BehaviourNode::set_result_children(NodeResult result)
{
    for (auto&& child : children)
    {
        child->set_result(result);
    }
}

NodeStatus BehaviourNode::get_status() const
{
    return status;
}

NodeResult BehaviourNode::get_result() const
{
    return result;
}

void BehaviourNode::tick(float dt)
{
    // explicitly check the statuses in order, so a node can transition fully through its states in one frame if needed

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


std::string BehaviourNode::get_name() const
{
    return name;
}
void BehaviourNode::on_enter()
{
    // base logic is to mark as running
    set_status(NodeStatus::RUNNING);
    set_result(NodeResult::IN_PROGRESS);

    // and this node's children as ready to run
    set_status_children(NodeStatus::READY);
    set_result_children(NodeResult::IN_PROGRESS);
}

void BehaviourNode::on_leaf_enter()
{
    set_status(NodeStatus::RUNNING);
    set_result(NodeResult::IN_PROGRESS);
}


void BehaviourNode::on_update(float)
{
    // no base logic that makes sense for every node
}

void BehaviourNode::on_exit()
{
    // base logic is to mark the node as done executing
    set_status(NodeStatus::SUSPENDED);
}

void BehaviourNode::on_success()
{
    set_status(NodeStatus::EXITING);
    set_result(NodeResult::SUCCESS);
}

void BehaviourNode::on_failure()
{
    set_status(NodeStatus::EXITING);
    set_result(NodeResult::FAILURE);
}
