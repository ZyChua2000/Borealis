#pragma once
#include <Core/Core.hpp>
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
        void AddNode(Ref<BehaviourNode> parent, Ref<BehaviourNode> child);
        void SetRootNode(Ref<BehaviourNode> root);
        Ref<BehaviourNode> GetRootNode();
        void update(float dt);

    private:
        Ref<BehaviourNode> rootNode;
        const char* treeName;
    };
}
