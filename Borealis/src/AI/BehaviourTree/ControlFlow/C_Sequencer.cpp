#include <BorealisPCH.hpp>
#include "AI/BehaviourTree/ControlFlow/C_Sequencer.hpp"
namespace Borealis
{
    C_Sequencer::C_Sequencer() : currentIndex(0)
    {}

    void C_Sequencer::on_enter()
    {
        currentIndex = 0;
        BehaviourNode::on_enter();
    }

    void C_Sequencer::on_update(float dt)
    {
        // if any child fails, the node fails
        // if all children succeed, the node succeeds
        Ref<BehaviourNode> currentNode = children[currentIndex];
        currentNode->tick(dt);

        if (currentNode->failed() == true)
        {
            on_failure();
        }
        else if (currentNode->succeeded() == true)
        {
            // move to the next node
            ++currentIndex;

            // if we hit the size, then all nodes suceeded
            if (currentIndex == children.size())
            {
                on_success();
            }
        }
    }
}