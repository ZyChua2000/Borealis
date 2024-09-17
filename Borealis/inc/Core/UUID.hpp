/******************************************************************************/
/*!
\file		UUID.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 21, 2024
\brief		Declares the UUID class for IDs for each object

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef UUID_HPP
#define UUID_HPP
namespace Borealis
{
	class UUID
	{
	public:
		/*!***********************************************************************
			\brief
				Default Constructor for UUID
		*************************************************************************/
		UUID();

		/*!***********************************************************************
			\brief
				Constructor for UUID
			\param id
				The id to be used for the UUID
		*************************************************************************/
		UUID(uint64_t id);

		/*!***********************************************************************
			\brief
				Copy Constructor for UUID
			\param[in] other
				The id to be used for the UUID
		*************************************************************************/
		UUID(const UUID& other) = default;

		/*!***********************************************************************
			\brief
				Operator overload to convert UUID to uint64_t
			\return
				The UUID as a uint64_t
		*************************************************************************/
		operator uint64_t() const { return mUUID; }
	private:
		uint64_t mUUID; //!< The UUID
	};  // class UUID
} // namespace Borealis

namespace std
{
	/*!***********************************************************************
		\brief
			Hash function for UUID
		\param[in] id
			The UUID to be hashed
	*************************************************************************/
	template <typename T> struct hash;
	template <>
	struct hash<Borealis::UUID>
	{
		std::size_t operator()(const Borealis::UUID& id) const
		{
			return static_cast<uint64_t>(id);
		}
	}; // struct hash
} // namespace std

#endif