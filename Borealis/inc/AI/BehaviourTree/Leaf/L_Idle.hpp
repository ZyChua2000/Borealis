#pragma once
/******************************************************************************
/*!
\file       L_Idle.cpp
\author     Joey Chua
\par        email: joeyjunyu.c@digipen.edu
\date       September 15, 2024
\brief      Declares the class for leaf node idle

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "AI/BehaviourTree/BehaviourNode.hpp"
namespace Borealis
{
    class L_Idle : public BaseNode<L_Idle>
    {
    public:
        L_Idle();

    protected:
        float timer;

        virtual void on_enter() override;
        virtual void on_update(float dt) override;
    };
}