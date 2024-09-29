#include "BorealisPCH.hpp"
#include "AI/BehaviourNode.hpp"
#include "AI/BehaviourTree.hpp"

namespace Borealis
{
    BehaviourTree::BehaviourTree() : rootNode(nullptr), treeName(nullptr)
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
    void BehaviourTree::AddNode(Ref<BehaviourNode> parent, Ref<BehaviourNode> child)
    {
        if (!parent) {
            if (!rootNode) {
                rootNode = child;  // If no root node exists, make the child the root
            }
            else {
                rootNode->add_child(child);  // Add to the root if no parent is specified
            }
        }
        else {
            parent->add_child(child);  // Add the child to the given parent
        }
    }
    void BehaviourTree::SetRootNode(Ref<BehaviourNode> root) 
    {
        rootNode = root;
    } 
    Ref<BehaviourNode> BehaviourTree::GetRootNode() 
    {
        return rootNode;
    }

}