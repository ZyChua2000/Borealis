#pragma once
#ifndef MATERIALEDITOR_HPP
#define MATERIALEDITOR_HPP

#include <Core/core.hpp>
#include <Scene/Entity.hpp>

namespace Borealis {
	class MaterialEditor
	{
	public:
		static void RenderEditor();
		static void RenderProperties(Ref<Material> const& material);
		static bool GetRender() { return mRender; }
		static void SetRender(bool render) { mRender = render; }
		
	private:
		static bool mRender;
	};
}

#endif