/******************************************************************************/
/*!
\file		Core.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	February 15, 2024
\brief		Declares the functions and macros for Core of the Borealis

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef CORE_HPP
#define CORE_HPP
#include <memory>
#if BOREALIS_DLL
#ifdef BOREALIS_BUILD_DLL
#define BOREALIS_API __declspec(dllexport)
#else
#define BOREALIS_API __declspec(dllimport)
#endif
#else
#define BOREALIS_API
#endif

#ifdef _DEB
	#define BOREALIS_DEBUGBREAK() __debugbreak()
	#define BOREALIS_ENABLE_ASSERTS
#else
	#define BOREALIS_DEBUGBREAK()
#endif

#define BOREALIS_EXPAND_MACRO(x) x
#define BOREALIS_STRINGIFY_MACRO(x) #x


#define BIND_EVENT(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Borealis
{
	template <typename ClassObject>
	using Ref = std::shared_ptr<ClassObject>;

	template <typename T, typename... Args>
	Ref<T> MakeRef(Args&&... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename ClassObject>
	using Scope = std::unique_ptr<ClassObject>;

	template <typename T, typename... Args>
	Scope<T> MakeScope(Args&&... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename classObject>
	class RefDraft
	{
	public:
		RefDraft(classObject* pointer) : rawPointer(pointer), refCount(1) {}
		RefDraft(const RefDraft& other) : rawPointer(other.rawPointer), refCount(other.refCount) { refCount++; }
		RefDraft& operator=(const RefDraft& other) { rawPointer = other.rawPointer; refCount = other.refCount; refCount++; return *this; }
		~RefDraft() { refCount--; if (refCount == 0) delete rawPointer; }
		classObject* operator->() { return rawPointer; }
		classObject& operator*() { return *rawPointer; }
	private:
		classObject* rawPointer;
		unsigned int refCount;
	};
}


#endif

