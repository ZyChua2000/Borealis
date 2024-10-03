/******************************************************************************
/*!
\file       L_CheckMouseClick.cpp
\author     Joey Chua
\par        email: joeyjunyu.c@digipen.edu
\date       September 15, 2024
\brief      Sample of mouse click node

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "AI/BehaviourTree/BehaviourNode.hpp"
namespace Borealis
{
    class L_CheckMouseClick : public BaseNode<L_CheckMouseClick>
    {
    protected:
        virtual void on_update(float dt);
    };
}
