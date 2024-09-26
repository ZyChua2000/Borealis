/******************************************************************************
/*!
\file       Components.cpp
\author     Chua Zheng Yang
\par        email: c.zhengyang@digipen.edu
\date       September 26, 2024
\brief      Defines the Component registrations

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include <rttr/registration>
#include <Scene/Components.hpp>

using namespace rttr;
namespace Borealis
{
    RTTR_REGISTRATION
    {
        registration::class_<TransformComponent>("TransformComponent")
        (metadata("Component", true))
             .constructor<>()
             .property("Translate", &TransformComponent::Translate)
             .property("Rotation", &TransformComponent::Rotation)
             .property("Scale", &TransformComponent::Scale)
             .method("GetTransform", &TransformComponent::GetTransform);

        registration::class_<SpriteRendererComponent>("SpriteRendererComponent")
            (metadata("Component", true))
            .constructor<>()
            .property("Colour", &SpriteRendererComponent::Colour)
            .property("Texture", &SpriteRendererComponent::Texture)
            .property("TilingFactor", &SpriteRendererComponent::TilingFactor);
    }

    std::vector<std::string> ComponentRegistry::GetComponentNames()
    {
        std::vector<std::string> componentNames;
        for (auto& t : type::get_types())
        {
            if (t.is_class() && t.get_metadata("Component"))
            {
				componentNames.push_back(t.get_name().to_string());
			}
		}
		return componentNames;
    }

    std::vector<std::string> ComponentRegistry::GetPropertyNames(std::string componentName)
    {
        type t = type::get_by_name(componentName);
        std::vector<std::string> properties;

        for (auto prop : t.get_properties())
        {
			properties.push_back(prop.get_name().to_string());
		}
        return properties;
    }
}