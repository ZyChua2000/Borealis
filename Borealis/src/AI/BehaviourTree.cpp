#include "BorealisPCH.hpp"
#include "AI/BehaviourNode.hpp"
#include "AI/BehaviourTree.hpp"

BehaviourTree::BehaviourTree() : rootNode(nullptr), treeName(nullptr)
{}

BehaviourTree::~BehaviourTree()
{
    delete rootNode;
}

void BehaviourTree::update(float dt)
{
    rootNode->tick(dt);

    // if the root node is complete in any way, restart it
    if (rootNode->is_running() == false)
    {
        rootNode->set_status(NodeStatus::READY);
    }
}