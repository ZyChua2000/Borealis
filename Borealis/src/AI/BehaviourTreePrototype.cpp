#include "BorealisPCH.hpp"
#include "AI/BehaviourNode.hpp"
#include "AI/BehaviourTreePrototype.hpp"
#include "AI/BehaviourTree.hpp"
#include "Scene/Entity.hpp"
namespace Borealis
{
    BehaviorTreePrototype::BehaviorTreePrototype()
        : rootNode(nullptr), previousNode(nullptr), treeName(nullptr)
    {
    }

    void BehaviorTreePrototype::build_tree(Entity ent)
    {

    }

    void BehaviorTreePrototype::add_node(NodeType type, int depth)
    {
        // Create a new node of the specified type
        BehaviourNode* newNode = create_node_of_type(type);  // Ensure you implement this function to return a proper node

        // Adjust the parent-child relationship based on depth
        if (depth == 0)
        {
            // This is the root node
            rootNode = newNode;
        }
        else
        {
            // Find the parent node based on the current depth
            BehaviourNode* parentNode = find_parent_node(depth);
            if (parentNode) 
            {
                // Add the new node as a child of the parent node
                parentNode->add_child(newNode);
            }
        }

        // Update the previousNode to the current node for subsequent calls
        previousNode = newNode;
    }

    void BehaviorTreePrototype::set_tree_name(const char* name)
    {
        treeName = name;
    }

    BehaviourNode* BehaviorTreePrototype::find_parent_node(int depth)
    {
        // Find the correct parent node based on the depth
        // This could be a stack-based approach or simply walking the tree from the rootNode
        BehaviourNode* currentNode = rootNode;

        // Traverse the tree to find the node at the desired depth
        while (currentNode && currentNode->get_depth() != depth - 1)
        {
            if (!currentNode->children.empty())
            {
                currentNode = currentNode->children.back();  // Move down the tree
            }
            else
            {
                return nullptr;  // No valid parent node found at the requested depth
            }
        }

        return currentNode;
    }

    void BehaviorTreePrototype::recursive_add(BehaviourNode* parent, BehaviourNode* child)
    {
        // Add the child node to the parent node recursively, building the tree
        if (parent)
        {
            parent->add_child(child);

            // For each child in the current node, add them recursively
            for (auto& childNode : child->children)
            {
                recursive_add(child, childNode);
            }
        }
    }

    // Helper function to create a node based on its type
    BehaviourNode* BehaviorTreePrototype::create_node_of_type(NodeType type) 
    {
        // Lookup the prototype by node type and clone it
        auto it = nodePrototypes.find(node_type_to_string(type));
        if (it != nodePrototypes.end()) {
            return it->second->clone();
        }
        return nullptr;
    }
    // Helper function to convert enum NodeType to string
    NodeType BehaviorTreePrototype::string_to_node_type(const std::string& typeStr)
    {
        // Extract the first two characters
        if (typeStr.size() < 2) {
            return NodeType::UNKNOWN;
        }

        std::string prefix = typeStr.substr(0, 2);

        // Map the prefix to the appropriate node type
        if (prefix == "C_") {
            return NodeType::CONTROLFLOW;
        }
        else if (prefix == "L_") {
            return NodeType::LEAF;
        }
        else if (prefix == "D_") {
            return NodeType::DECORATOR;
        }

        return NodeType::UNKNOWN;  // Return INVALID if the prefix doesn't match any known type
    }



}