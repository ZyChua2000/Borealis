/******************************************************************************/
/*!
\file		Serialiser.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 14, 2024
\brief		Declares the class for Serialiser

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef SERIALISER_HPP
#define SERIALISER_HPP
#include <Core/Core.hpp>
#include <Scene/Scene.hpp>
#include <yaml-cpp/yaml.h>

namespace YAML
{
	class Emitter;
}
namespace Borealis
{
	class BehaviourNode;
	class BehaviourTree;
	class Serialiser
	{
	public:
		Serialiser(const Ref<Scene>& scene);
		void ParseTree(YAML::Node& node, Ref<BehaviourNode> parentNode, BehaviourTree& tree, int parentDepth);

		bool SerialiseScene(const std::string& filepath);
		bool DeserialiseScene(const std::string& filepath);

		static bool SerialiseEditorStyle();
		static bool DeserialiseEditorStyle();
		static bool SerializeBehaviourNode(YAML::Emitter& out, const Ref<BehaviourNode> node);
	private:
		Ref<Scene> mScene;

	};
}

#endif