/******************************************************************************
/*!
\file       Font.hpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 19, 2024
\brief      Declares

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef Font_HPP
#define Font_HPP

#include <Graphics/Texture.hpp>

namespace Borealis
{
	struct FontQuadBound
	{
		double top;
		double bottom;
		double left;
		double right;
	};
	struct FontGlyph
	{
		double advance;
		FontQuadBound altasBound;
		FontQuadBound planeBound;
	};

	struct FontInfo
	{
		double ascenderY;
		double descenderY;
		std::unordered_map<char, FontGlyph> glyphs;
		std::map<std::pair<uint32_t, uint32_t>, double> kernings;
		Ref<Texture2D> fontAtlas;
	};

	class Font
	{
	public:
		Font();
		Font(Ref<FontInfo> fontInfo);
		~Font();

		Ref<FontInfo> GetFontInfo() const;
		void SetAtlasTexture(Ref<Texture2D> atlas); // TEMP to remove

		Ref<Texture2D> GetAtlasTexture() const;

	private:
		Ref<FontInfo> mFontInfo;
		Ref<Texture2D> mAtlasTexture = nullptr;
	};
}

#endif
