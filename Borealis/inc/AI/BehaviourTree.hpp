#pragma once
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

        void update(float dt);

    private:
        BehaviourNode* rootNode;
        const char* treeName;
    };
}
