/******************************************************************************
/*!
\file       BehaviourTree.hpp
\author     Joey Chua
\par        email: joeyjunyu.c@digipen.edu
\date       September 15, 2024
\brief      Declares the class for behaviour tree
Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef BEHAVIOURTREE_HPP
#define BEHAVIOURTREE_HPP

#include <Core/Core.hpp>
#include <string>
namespace Borealis
{
    // forward declaration
    class BehaviourNode;
    //class BehaviorTreePrototype;

    class BehaviourTree
    {
        //friend class BehaviorTreePrototype;
    public:
        BehaviourTree();
        ~BehaviourTree();
        void AddNode(Ref<BehaviourNode> parent, Ref<BehaviourNode> child, int depth);
        void SetRootNode(Ref<BehaviourNode> root);
        Ref<BehaviourNode> GetRootNode();
        void update(float dt);
        void SetBehaviourTreeName(std::string&& name); //overload incase someone creates using "NAME"
        void SetBehaviourTreeName(std::string& name);
        std::string GetBehaviourTreeName() const;

    private:
        Ref<BehaviourNode> rootNode;
        Ref<BehaviourNode> previousNode;
        std::string treeName;
    };
}
