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
        void AddNode(BehaviourNode* parent, BehaviourNode* child);
        void SetRootNode(BehaviourNode* root);
        BehaviourNode* GetRootNode();
        void update(float dt);

    private:
        BehaviourNode* rootNode;
        const char* treeName;
    };
}
