/******************************************************************************/
/*!
\file		FontImporter.hpp
\author 	Chan Guo Geng Gordon
\par    	email: g.chan\@digipen.edu
\date   	September 18, 2024
\brief		Declares the class Font Importer in Level Editor

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#ifndef FONT_IMPORTER_HPP
#define FONT_IMPORTER_HPP

#include <string>

#include <Core/core.hpp>
#include <Scene/Components.hpp>

namespace Borealis
{
	struct FontInfo;
	class FontImporter
	{
	public:
		static FontInfo generateAtlas(const char* fontFilename);
	private:
	};
}

#endif