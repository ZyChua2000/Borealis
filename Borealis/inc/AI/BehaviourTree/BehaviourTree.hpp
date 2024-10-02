#pragma once
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
        void SetBehaviourTreeName(std::string&& name);
        std::string GetBehaviourTreeName() const;

    private:
        Ref<BehaviourNode> rootNode;
        Ref<BehaviourNode> previousNode;
        std::string treeName;
    };
}
