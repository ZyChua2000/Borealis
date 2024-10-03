/******************************************************************************
/*!
\file       L_Idle.cpp
\author     Joey Chua
\par        email: joeyjunyu.c@digipen.edu
\date       September 15, 2024
\brief      Defines the class for leaf node idle

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

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