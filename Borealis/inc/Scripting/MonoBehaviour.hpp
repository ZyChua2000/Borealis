/******************************************************************************/
/*!
\file		MonoBehaviour.hpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	September 07, 2024
\brief		Declares the class for MonoBehaviour Scripts

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <Scripting/Behaviour.hpp>

#ifndef MONO_BEHAVIOUR_HPP
#define MONO_BEHAVIOUR_HPP

namespace Borealis
{
	class MonoBehaviour : public Behaviour
	{
	public:
		virtual void Awake() = 0;
		virtual void FixedUpdate() = 0;
		virtual void LateUpdate() = 0;
		virtual void Update() = 0;
		virtual void Start() = 0;
		virtual void OnDestroy() = 0;
		virtual void OnCollisionEnter() = 0;
		virtual void OnCollisionExit() = 0;
		virtual void OnCollisionStay() = 0;
		virtual void OnTriggerEnter() = 0;
		virtual void OnTriggerExit() = 0;
		virtual void OnTriggerStay() = 0;
		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		virtual void OnRender() = 0;
		virtual void OnMouseDown() = 0;
		virtual void OnMouseUp() = 0;
		virtual void OnMouseDrag() = 0;
		virtual void OnMouseEnter() = 0;
		virtual ~MonoBehaviour() = default;
	};
}
#endif