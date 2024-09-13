/******************************************************************************/
/*!
\file		BehaviorTreeBuilder.cpp
\project	CS380/CS580 AI Framework
\author		Dustin Holmes
\summary	Builds behavior trees from prototypes

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/
#include "BorealisPCH.hpp"

#include "AI/BehaviorTreeBuilder.hpp"

namespace
{
    const unsigned bufferSize = 255;
    char buffer[bufferSize];
}

namespace fs = std::filesystem;
std::unordered_map<std::string, NodeType> nodeTypeMap;

//bool BehaviorTreeBuilder::initialize()
//{
//    std::cout << "    Initializing Behavior Tree Builder..." << std::endl;
//
//    bool result = true;
//
//    // get a list of all the behavior tree files
//
//    // add all the file entries to a temp vector
//    std::vector<fs::path> paths;
//
//    for (auto && entry : dir)
//    {
//        if (fs::is_regular_file(entry) == true)
//        {
//            paths.emplace_back(std::move(entry.path()));
//        }
//    }
//
//    // ensure that we have the same number of behavior trees as those registered
//    if (paths.size() == static_cast<size_t>(BehaviorTreeTypes::NUM_ENTRIES))
//    {
//        prototypes.resize(paths.size());
//
//        // for each path, deserialize the file into a behavior tree prototype
//        for (const auto & path : paths)
//        {
//            if (deserialize_tree(path) == false)
//            {
//                result = false;
//                break;
//            }
//        }
//
//        std::cout << "        Prototyped " << prototypes.size() << " Behavior Trees" << std::endl;
//    }
//    else
//    {
//        std::cout << "Expected to find " << static_cast<size_t>(BehaviorTreeTypes::NUM_ENTRIES) <<
//            " behavior tree files, but found " << paths.size() << std::endl;
//
//        std::cout << "Behavior Tree files found:" << std::endl;
//        for (const auto & path : paths)
//        {
//            std::cout << path.filename() << ", ";
//        }
//
//        std::cout << std::endl << "Behavior Tree files expected:" << std::endl;
//        for (const auto & n : nodeNames)
//        {
//            std::cout << n << ", ";
//        }
//        std::cout << std::endl;
//
//        result = false;
//    }
//
//    return result;
//}
// 
// // Function to extract the NodeType based on the prefix of the node name
NodeType BTBuilderHelper::get_node_type_from_prefix(const std::string& nodeName)
{
    if (nodeName.find("C_") == 0)  // If the node name starts with "C_"
        return NodeType::CONTROLFLOW;
    else if (nodeName.find("D_") == 0)  // If the node name starts with "D_"
        return NodeType::DECORATOR;
    else if (nodeName.find("L_") == 0)  // If the node name starts with "L_"
        return NodeType::LEAF;

    return NodeType::UNKNOWN;  // Return UNKNOWN if no prefix matches
}
// Function to read node names from a file and determine their types based on prefix
void load_node_types_from_file(const std::string& filename)
{
    std::ifstream file(filename);
    std::string nodeName;

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // Read each line, which is a node name
    while (std::getline(file, nodeName))
    {
        const std::string& container = nodeName;
        // Determine the NodeType based on the prefix
        NodeType type = BTBuilderHelper::get_node_type_from_prefix(container);

        // Add the node and its type to the map
        nodeTypeMap[nodeName] = type;
    }
}
//void BehaviorTreeBuilder::shutdown()
//{
//    std::cout << "    Shutting Down Behavior Tree Builder..." << std::endl;
//    prototypes.clear();
//}

//void BehaviorTreeBuilder::build_tree(BehaviorTreeTypes type, BehaviorAgent *agent)
//{
//    prototypes[static_cast<size_t>(type)].build_tree(agent);
//}
//
//bool BehaviorTreeBuilder::deserialize_tree(const fs::path &filepath)
//{
//    FILE *file;
//
//    // files aren't json, but we can still use some serialization code
//    if (Serialization::open_file(&file, filepath, true) == false)
//    {
//        return false;
//    }
//
//    const auto treeType = deserialize_tree_type(file);
//
//    // make sure we found a valid tree type
//    if (treeType == BehaviorTreeTypes::NUM_ENTRIES)
//    {
//        return false;
//    }
//
//    BehaviorTreePrototype &target = prototypes[static_cast<size_t>(treeType)];
//    target.set_tree_name(tree_type_to_tree_name(treeType));
//
//    NodeTypes nodeType;
//    int depth;
//
//    while (deserialize_node(file, nodeType, depth) == true)
//    {
//        if (nodeType != NodeTypes::NUM_ENTRIES)
//        {
//            target.add_node(nodeType, depth);
//        }
//    }
//
//    return true;
//}

//BehaviorTreeTypes BehaviorTreeBuilder::deserialize_tree_type(FILE *file)
//{
//    const auto result = fscanf_s(file, "TREENAME(%s", buffer, bufferSize);
//
//    // make sure characters were read
//    if (result == 1)
//    {
//        // buffer will contain the closing paranthesis, change it to null terminator
//        const auto length = std::strlen(buffer);
//        buffer[length - 1] = '\0';
//
//        const auto treeType = string_to_behavior_tree_type(buffer);
//
//        // make sure a valid tree type was returned
//        if (treeType != BehaviorTreeTypes::NUM_ENTRIES)
//        {
//            return treeType;
//        }
//        else
//        {
//            std::cout << "Couldn't match tree name (" << buffer << ") to tree type, is it in Trees.def and spelled correctly?" << std::endl;
//            return BehaviorTreeTypes::NUM_ENTRIES;
//        }
//    }
//    else
//    {
//        std::cout << "Couldn't read tree name from file" << std::endl;
//        return BehaviorTreeTypes::NUM_ENTRIES;
//    }
//}

//bool BehaviorTreeBuilder::deserialize_node(FILE *file, NodeType &type, int &depth)
//{
//    int depthLocal;
//
//    const auto result = fscanf_s(file, "\nTREENODE(%s %d)", buffer, bufferSize, &depthLocal);
//
//    // make sure both fields were read
//    if (result == 2)
//    {
//        // buffer wil contain the delimiting comma, change it to null terminator
//        const auto length = std::strlen(buffer);
//        buffer[length - 1] = '\0';
//
//        const auto nodeType = string_to_node_type(buffer);
//
//        // make sure a valid node type was returned
//        if (nodeType != NodeTypes::NUM_ENTRIES)
//        {
//            type = nodeType;
//            depth = depthLocal;
//            return true;
//        }
//        else
//        {
//            std::cout << "Couldn't match node name (" << buffer << ") to node type, is it in Nodes.def and spelled correctly?" << std::endl;
//            return false;
//        }
//    }
//    // something went wrong
//    else if (result != EOF)
//    {
//        std::cout << "Error deserializing node, incorrect number of fields read" << std::endl;
//        return false;
//    }
//    else
//    {
//        // end of file was reached, no error
//        return false;
//    }
//}
