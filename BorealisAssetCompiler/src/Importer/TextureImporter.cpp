/******************************************************************************
/*!
\file       TextureImporter.cpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 29, 2024
\brief      Defines

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Importer/TextureImporter.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//#include "ispc_texcomp.h"

#define FOURCC_DX10 0x30315844  // 'DX10' in ASCII
#define DXGI_FORMAT_BC7_UNORM 98  // The BC7 format value for DX10 header

namespace BorealisAssetCompiler
{
    void TextureImporter::SaveDDSFile(const std::string& filePath, int width, int height, const std::vector<uint8_t>& compressedData)
    {
        DDSHeader header = {};
        header.dwMagic = 0x20534444;  // 'DDS '
        header.dwSize = 124;
        header.dwFlags = 0x1007;  // DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT
        header.dwHeight = height;
        header.dwWidth = width;
        header.dwPitchOrLinearSize = (width / 4) * (height / 4) * 16;  // Compressed size for BC7 blocks
        header.dwMipMapCount = 1;

        header.ddpf.dwSize = 32;
        header.ddpf.dwFlags = 4;  // DDPF_FOURCC
        header.ddpf.dwFourCC = FOURCC_DX10;  // 'DX10' FourCC for BC7

        header.ddsCaps.dwCaps1 = 0x1000;  // DDSCAPS_TEXTURE

        // DX10 extended header
        DDSHeaderDX10 dx10Header = {};
        dx10Header.dxgiFormat = DXGI_FORMAT_BC7_UNORM;
        dx10Header.resourceDimension = 3;  // DDS_DIMENSION_TEXTURE2D
        dx10Header.arraySize = 1;

        // Write the header and compressed data to the DDS file
        std::ofstream outFile(filePath, std::ios::binary);
        if (outFile.is_open()) {
            outFile.write(reinterpret_cast<char*>(&header), sizeof(header));
            outFile.write(reinterpret_cast<char*>(&dx10Header), sizeof(dx10Header));
            outFile.write(reinterpret_cast<const char*>(compressedData.data()), compressedData.size());
            outFile.close();
        }
    }

    void TextureImporter::SaveFile(std::filesystem::path const& sourcePath, std::filesystem::path & cachePath)
    {
        int width, height, channels;
        unsigned char* imageData = stbi_load(sourcePath.string().c_str(), &width, &height, &channels, 4); // Force 4 channels (RGBA)
        if (!imageData) {
            std::cerr << "Failed to load image\n";
            return;
        }

        bc7_enc_settings settings;
        GetProfile_alpha_basic(&settings);

        rgba_surface srcSurface;
        srcSurface.ptr = imageData;
        srcSurface.width = width;
        srcSurface.height = height;
        srcSurface.stride = width * 4;

        int compressedSize = (width / 4) * (height / 4) * 16;
        std::vector<uint8_t> compressedData(compressedSize);

        CompressBlocksBC7(&srcSurface, compressedData.data(), &settings);

        std::string cacheString = cachePath.replace_extension(".dds").string();

        SaveDDSFile(cacheString.c_str(), width, height, compressedData);

        stbi_image_free(imageData);
    }
}

