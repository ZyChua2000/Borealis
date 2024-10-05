/******************************************************************************
/*!
\file       FontImporter.hpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 30, 2024
\brief      Declares

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef FontImporter_HPP
#define FontImporter_HPP

#include <unordered_map>
#include <map>
#include <filesystem>

namespace BorealisAssetCompiler
{
	struct FontQuadBound
	{
		double top = 0.0;
		double bottom = 0.0;
		double left = 0.0;
		double right = 0.0;
	};

	struct FontGlyph
	{
		double advance = 0.0;
		FontQuadBound altasBound;
		FontQuadBound planeBound;
	};

	struct FontInfo
	{
		double ascenderY = 0.0;
		double descenderY = 0.0;
		std::unordered_map<char, FontGlyph> glyphs;
		std::map<std::pair<uint32_t, uint32_t>, double> kernings;
		std::shared_ptr<void*> atlas = nullptr;
	};

	class FontImporter
	{
	public:
		static void SaveFile(std::filesystem::path const& fontPath, std::filesystem::path& cachePath);
	private:
		static FontInfo generateAtlas(std::filesystem::path fontPath, std::filesystem::path cachePath);
		static void SerializeFontInfo(FontInfo const& fontInfo, std::filesystem::path const& cachePath);
	};
}

#endif
