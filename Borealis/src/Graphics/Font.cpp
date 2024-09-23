/******************************************************************************
/*!
\file       Font.cpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 19, 2024
\brief      Defines

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include <BorealisPCH.hpp>


#include <Graphics/Texture.hpp>
#include <Graphics/Font.hpp>

namespace Borealis
{
	static Ref<Font> font;

	Font::Font()
	{
		mFontInfo = nullptr;
	}

	Font::Font(Ref<FontInfo> fontInfo)
	{
		mFontInfo = fontInfo;
	}

	Font::~Font()
	{

	}

	Ref<FontInfo> Font::GetFontInfo() const
	{
		return mFontInfo;
	}

	Ref<Texture2D> Font::GetAtlasTexture() const
	{
		return mFontInfo->fontAtlas;
	}

	void Font::SetDefaultFont(Ref<Font> defaultFont)
	{
		font = defaultFont;
	}

	Ref<Font> Font::GetDefaultFont()
	{
		if (!font)
			return nullptr;
		return font;
	}
}

