/******************************************************************************/
/*!
\file		BehaviorTreeBuilder.h
\project	CS380/CS580 AI Framework
\author		Dustin Holmes
\summary	Builds behavior trees from prototypes

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "AI/BehaviourTreePrototype.hpp"
#include "AI/BehaviourNode.hpp"
#include <vector>

namespace BTBuilderHelper
{
    // Function to extract the NodeType based on the prefix of the node name
    NodeType get_node_type_from_prefix(const std::string& nodeName);
}
class BehaviourTreeBuilder
{
public:

    bool initialize();
    void shutdown();

    void build_tree(); //type of tree will be read through the file name, need to add agent version later.

private:
    std::vector<BehaviorTreePrototype> prototypes;

    bool deserialize_tree(const std::filesystem::path &filepath);

    NodeType deserialize_tree_type(FILE *file);
    bool deserialize_node(FILE *file, NodeType &type, int &depth);
};