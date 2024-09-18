/******************************************************************************/
/*!
\file		FontImporter.cpp
\author 	Chan Guo Geng Gordon
\par    	email: g.chan\@digipen.edu
\date   	September 18, 2024
\brief		Declares the class Font Importer in Level Editor

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#include <Assets/FontImporter.hpp>

#include <msdf-atlas-gen/msdf-atlas-gen.h>

namespace Borealis
{
	template<typename T, typename S, int N, msdf_atlas::GeneratorFunction<S, N> GenFunc>
	static Ref<Texture2D> CreateAndCacheAtlas(const std::string& fontName, float fontSize, const std::vector<msdf_atlas::GlyphGeometry>& glyphs,
		const msdf_atlas::FontGeometry& fontGeometry, uint32_t width, uint32_t height)
	{
		msdf_atlas::GeneratorAttributes attributes;
		attributes.config.overlapSupport = true;
		attributes.scanlinePass = true;

		msdf_atlas::ImmediateAtlasGenerator<S, N, GenFunc, msdf_atlas::BitmapAtlasStorage<T, N>> generator(width, height);
		generator.setAttributes(attributes);
		generator.setThreadCount(8);
		generator.generate(glyphs.data(), (int)glyphs.size());

		msdfgen::BitmapConstRef<T, N> bitmap = (msdfgen::BitmapConstRef<T, N>)generator.atlasStorage();

		msdfgen::savePng(bitmap, "Test.png");

		Ref<Texture2D> texture = Texture2D::Create(bitmap.width, bitmap.width);
		texture->SetData((void*)bitmap.pixels, bitmap.width * bitmap.height * 4);
		return texture;
	}

	Ref<Texture2D> FontImporter::generateAtlas(const char* fontFilename)
	{
		Ref<Texture2D> atlas = nullptr;
		if (msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype())
		{
			if (msdfgen::FontHandle* font = loadFont(ft, "C:\\Windows\\Fonts\\arialbd.ttf"))
			{
				std::vector<msdf_atlas::GlyphGeometry> glyphs;

				static const uint32_t ranges[] =
				{
					0x0020, 0x00FF,
					0
				};

				msdf_atlas::Charset charSet;
				for (int range = 0; range < 2; range += 2)
				{
					for (uint32_t c = ranges[range]; c <= ranges[range + 1]; c++)
					{
						charSet.add(c);
					}
				}
				double fontScale = 1.0;
				msdf_atlas::FontGeometry fontGeometry = msdf_atlas::FontGeometry(&glyphs);
				int loadedGlyphs = fontGeometry.loadCharset(font, fontScale, charSet);

				msdf_atlas::TightAtlasPacker packer;
				packer.setPixelRange(2.0);
				packer.setMiterLimit(1.0);
				packer.setOuterPixelPadding(0);
				packer.setScale(40.0);
				int remain = packer.pack(glyphs.data(), (int)glyphs.size());

				int width, height;
				packer.getDimensions(width, height);


#define LCG_MULTIPLIER 6364136223846793005ull
#define LCG_INCREMENT 1442695040888963407ull
#define ANGLE_THRESHOULD 3
				int threadCount = 8;
				uint64_t coloringSeed = 0;
				bool expensiveColoring = false;
				if (expensiveColoring) {
					msdf_atlas::Workload([&glyphs, &coloringSeed](int i, int threadNo) -> bool {
						unsigned long long glyphSeed = (LCG_MULTIPLIER * (coloringSeed ^ i) + LCG_INCREMENT) * !!coloringSeed;
						glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, ANGLE_THRESHOULD, glyphSeed);
						return true;
						}, glyphs.size()).finish(threadCount);
				}
				else {
					unsigned long long glyphSeed = coloringSeed;
					for (msdf_atlas::GlyphGeometry& glyph : glyphs) {
						glyphSeed *= LCG_MULTIPLIER;
						glyph.edgeColoring(msdfgen::edgeColoringInkTrap, ANGLE_THRESHOULD, glyphSeed);
					}
				}

				atlas = CreateAndCacheAtlas<uint8_t, float, 4, msdf_atlas::mtsdfGenerator>("Test", (float)packer.getScale(), glyphs, fontGeometry, width, height);

				msdfgen::destroyFont(font);
			}
			msdfgen::deinitializeFreetype(ft);
		}

		return atlas;
	}
}
