/******************************************************************************/
/*!
\file		BehaviorTreePrototype.hpp
\project	
\author		
\summary	Stores the structure of behavior trees read from files

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/
#pragma once
//#include "../inc/AI/BehaviourNode.hpp"
#include <memory>
// forward declaration
class BehaviourNode;
//class BehaviorTreePrototype;

class BehaviorTreePrototype
{
public:
    BehaviorTreePrototype();
        
    // Build the behavior tree and attach it to the agent
    //void build_tree(BehaviorAgent* agent);
    void build_tree(); //for now build trees without agent 

    // Add a node to the tree prototype with a given type and depth
    void add_node(NodeType type, int depth);

    // Set the name of the tree
    void set_tree_name(const char* name);

private:
    // Recursive function to build the tree from the added nodes
    void recursive_add(BehaviourNode* parent, BehaviourNode* child);

    // Tree root node
    BehaviourNode* rootNode;

    // Tracks the most recently added node for managing hierarchy
    BehaviourNode* previousNode;

    // Name of the behavior tree
    const char* treeName;

    // Function to find the correct parent node based on depth
    BehaviourNode* find_parent_node(int depth);
};
