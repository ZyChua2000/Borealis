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
		UUID();
		UUID(uint64_t id);
		UUID(const UUID& other) = default;

		operator uint64_t() const { return mUUID; }
	private:
		uint64_t mUUID;
	};
}

namespace std
{
	template <>
	struct hash<Borealis::UUID>
	{
		std::size_t operator()(const Borealis::UUID& id) const
		{
			return static_cast<uint64_t>(id);
		}
	};
}

#endif