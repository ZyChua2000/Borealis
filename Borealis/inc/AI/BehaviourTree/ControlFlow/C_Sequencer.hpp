/******************************************************************************
/*!
\file       C_Sequencer.hpp
\author     Joey Chua
\par        email: joeyjunyu.c@digipen.edu
\date       September 15, 2024
\brief      Sample of sequencer node

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef C_SEQUENCER_HPP
#define C_SEQUENCER_HPP
#include "AI/BehaviourTree/BehaviourNode.hpp"
namespace Borealis
{
    class C_Sequencer : public BaseNode<C_Sequencer>
    {
    public:
        C_Sequencer();
    protected:
        size_t currentIndex;

        virtual void on_enter() override;
        virtual void on_update(float dt) override;

    };
}
