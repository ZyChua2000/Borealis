/******************************************************************************/
/*!
\file		Object.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	September 07, 2024
\brief		Declares the class for Object Scripts

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>
namespace Borealis
{
	class Object
	{
	public:
		int GetInstanceID() const { return mInstanceID; };
		
		//std::string ToString();

		static void Destroy(Object obj, float t)
		{
			// Dispatch destroy message
		}
		static Object Instantiate(Object original)
		{
			// Dispatch instantiate message
			return original;
		}

		bool operator==(const Object& rhs) const
		{
			return mInstanceID == rhs.mInstanceID;
		}
		bool operator!=(const Object& rhs) const
		{
			return mInstanceID != rhs.mInstanceID;
		}
	protected:
		int mInstanceID;
		static int mInstanceCounter;
	};
}

#endif