/******************************************************************************/
/*!
\file		MeshImporter.cpp
\author 	Chan Guo Geng Gordon
\par    	email: g.chan\@digipen.edu
\date   	September 12, 2024
\brief		Declares the class Mesh Importer in Level Editor

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#include <Assets/MeshImporter.hpp>

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

		//TextureSpecification spec;
		//spec.Width = bitmap.width;
		//spec.Height = bitmap.height;
		//spec.Format = ImageFormat::RGB8;
		//spec.GenerateMips = false;

		Ref<Texture2D> texture = Texture2D::Create(bitmap.width, bitmap.width);
		texture->SetData((void*)bitmap.pixels, bitmap.width * bitmap.height * 4);
		return texture;
	}

	Ref<Texture2D> MeshImporter::generateAtlas(const char* fontFilename)
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

				atlas = CreateAndCacheAtlas<uint8_t, float, 3, msdf_atlas::msdfGenerator>("Test", (float)packer.getScale(), glyphs, fontGeometry, width, height);

				msdfgen::destroyFont(font);
			}
			msdfgen::deinitializeFreetype(ft);
		}

		return atlas;
	}
	Ref<Model> MeshImporter::LoadFBXModel(const std::string& path)
	{
		//if (msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype()) {
		//	if (msdfgen::FontHandle* font = loadFont(ft, "C:\\Windows\\Fonts\\arialbd.ttf")) {
		//		msdfgen::Shape shape;
		//		if (loadGlyph(shape, font, 'B', msdfgen::FONT_SCALING_EM_NORMALIZED)) {
		//			shape.normalize();
		//			//                      max. angle
		//			edgeColoringSimple(shape, 3.0);
		//			//          output width, height
		//			msdfgen::Bitmap<float, 3> msdf(32, 32);
		//			//                            scale, translation (in em's)
		//			msdfgen::SDFTransformation t(msdfgen::Projection(32.0, msdfgen::Vector2(0.125, 0.125)), msdfgen::Range(0.125));
		//			msdfgen::generateMSDF(msdf, shape, t);
		//			msdfgen::savePng(msdf, "output.png");
		//		}
		//		msdfgen::destroyFont(font);
		//	}
		//	msdfgen::deinitializeFreetype(ft);
		//}

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			return nullptr;
		}

		//BOREALIS_CORE_TRACE("FBX load from {0}", path);

		Model model;
		ProcessNode(scene->mRootNode, scene, model);
		return MakeRef<Model>(model);
	}

	Mesh MeshImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<glm::vec3> vertices;
		std::vector<unsigned int> indices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;

			vertices.push_back(vector);

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;

			normals.push_back(vector);

			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				texCoords.push_back(vec);
			}
			else
				texCoords.push_back(glm::vec2(0.0f, 0.0f));
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		return Mesh(vertices, indices, normals, texCoords);
	}

	void MeshImporter::ProcessNode(aiNode* node, const aiScene* scene, Model& model)
	{
		for (int i{}; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			model.mMeshes.push_back(ProcessMesh(mesh, scene));
		}

		for (int i{}; i < node->mNumChildren; ++i)
		{
			ProcessNode(node->mChildren[i], scene, model);
		}
	}
}