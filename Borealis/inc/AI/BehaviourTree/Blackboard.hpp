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
#ifndef BLACKBOARD_HPP
#define BLACKBOARD_HPP

#include <any>
#include <unordered_map>
#include <string>
#include <optional>
#include <type_traits>
#include <stdexcept>
#include <Core/LoggerSystem.hpp>
namespace Borealis
{

    class Blackboard
    {
    public:
        /*!***********************************************************************
            \brief
                Sets the value of a given key in the blackboard
            \tparam T
                The type of the value to set
            \param[in] key
                The key to set the value to
            \param[in] value
                The value to set
        *************************************************************************/
        template <typename T>
        void SetValue(const std::string& key, const T& value);

        /*!***********************************************************************
            \brief
                Attempts to retrieve the value of a given key in the blackboard
            \tparam T
                The type of the value to get
            \param[in] key
                The key to get the value from
            \return
                An optional containing the value if the key exists, 
                empty optional otherwise
        *************************************************************************/
        template <typename T>
        std::optional<T> GetValue(const std::string& key) const;

        /*!***********************************************************************
            \brief
                Option to directly check if the key exists in the blackboard
            \param[in] key
                The key to check
            \return
				True if the key exists, false otherwise
        *************************************************************************/
        bool HasKey(const std::string& key) const;

    private:
        std::unordered_map<std::string, std::any> mBlackboardData; // data set in the blackboard
    };

    template<typename T>
    inline void Blackboard::SetValue(const std::string& key, const T& value)
    {
        BOREALIS_CORE_ASSERT(std::is_copy_constructible<T>::value, "Attempting to add non-copy-constructible type into blackboard");
        mBlackboardData[key] = value;
    }

    template<typename T>
    inline std::optional<T> Blackboard::GetValue(const std::string& key) const
    {
        const auto result = mBlackboardData.find(key);

        // Make sure the key exists
        if (result != mBlackboardData.end())
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

    inline bool Blackboard::HasKey(const std::string& key) const
    {
        return mBlackboardData.find(key) != mBlackboardData.end();
    }
}
#endif // BLACKBOARD_HPP