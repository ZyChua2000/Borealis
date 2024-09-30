#include <BorealisPCH.hpp>
#include "AI//BehaviourTree/Leaf/L_Idle.hpp"
#include <Core/InputSystem.hpp>
#include <Core/KeyCodes.hpp>
#include <Core/LoggerSystem.hpp>
namespace Borealis
{
    L_Idle::L_Idle()
    {}

    void L_Idle::on_enter()
    {
        timer = 3.f;
        BehaviourNode::on_leaf_enter();
    }

    void L_Idle::on_update(float dt)
    {
        timer -= dt;

        BOREALIS_CORE_TRACE("Idling now, time is {}", timer);

        if (timer < 0.0f)
        {
            BOREALIS_CORE_TRACE("Idling completed");
            on_success();
        }

    }
}