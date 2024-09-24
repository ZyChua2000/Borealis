#pragma once
#ifndef MATERIALEDITOR_HPP
#define MATERIALEDITOR_HPP

namespace Borealis {
	class MaterialEditor
	{
	public:
		static void RenderEditor();
		static bool GetRender() { return mRender; }
		static void SetRender(bool render) { mRender = render; }
		
	private:
		static bool mRender;
	};
}

#endif