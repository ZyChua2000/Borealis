#pragma once
#include "AI/BehaviourNode.hpp"
namespace Borealis
{
    class L_CheckMouseClick : public BaseNode<L_CheckMouseClick>
    {
    protected:
        virtual void on_update(float dt);
    };
}
