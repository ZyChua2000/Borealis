#include <BorealisPCH.hpp>
#include "AI/L_Idle.hpp"
#include <Core/InputSystem.hpp>
#include <Core/KeyCodes.hpp>
#include <Core/LoggerSystem.hpp>
namespace Borealis
{
    L_Idle::L_Idle() : timer(3.f)
    {}

    void L_Idle::on_enter()
    {

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