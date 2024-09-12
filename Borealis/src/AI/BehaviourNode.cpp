#include "../inc/AI/BehaviourNode.hpp"
#include "../inc/AI/BehaviourTree.hpp"

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