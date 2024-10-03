#pragma once
/******************************************************************************
/*!
\file       RegisterNodes.hpp
\author     Joey Chua
\par        email: joeyjunyu.c@digipen.edu
\date       September 15, 2024
\brief      Declares the blackboard class used to share data within behaviour nodes

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include <any>
#include <unordered_map>
#include <string>
#include <optional>
#include <type_traits>
#include <stdexcept>
namespace Borealis
{

    class Blackboard
    {
    public:
        // Sets the value of a given key in the blackboard
        template <typename T>
        void set_value(const std::string& key, const T& value);

        // Attempts to get the value of a given key and cast it to the correct type
        template <typename T>
        std::optional<T> get_value(const std::string& key) const;

        // Option to directly check if the key exists in the blackboard
        bool has_key(const std::string& key) const;

    private:
        std::unordered_map<std::string, std::any> data;
    };

    template<typename T>
    inline void Blackboard::set_value(const std::string& key, const T& value)
    {
        static_assert(std::is_copy_constructible<T>::value, "Attempting to add non-copy-constructible type into blackboard");
        data[key] = value;
    }

    template<typename T>
    inline std::optional<T> Blackboard::get_value(const std::string& key) const
    {
        const auto result = data.find(key);

        // Make sure the key exists
        if (result != data.end())
        {
            try
            {
                // Attempt to cast the value to the expected type
                T value = std::any_cast<T>(result->second);
                return value; // Successfully return the cast value
            }
            catch (const std::bad_any_cast&)
            {
                // Type mismatch, return empty optional
                return std::nullopt;
            }
        }
        else
        {
            // Key was not found, return empty optional
            return std::nullopt;
        }
    }

    inline bool Blackboard::has_key(const std::string& key) const
    {
        return data.find(key) != data.end();
    }
}