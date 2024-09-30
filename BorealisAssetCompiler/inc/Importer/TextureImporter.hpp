/******************************************************************************
/*!
\file       TextureImporter.hpp
\author     Chan Guo Geng Gordon
\par        email: g.chan/@digipen.edu
\date       September 29, 2024
\brief      Declares

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef TextureImporter_HPP
#define TextureImporter_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace BorealisAssetCompiler
{
    struct DDSHeader {
        uint32_t dwMagic;
        uint32_t dwSize;
        uint32_t dwFlags;
        uint32_t dwHeight;
        uint32_t dwWidth;
        uint32_t dwPitchOrLinearSize;
        uint32_t dwDepth;
        uint32_t dwMipMapCount;
        uint32_t dwReserved1[11];
        struct {
            uint32_t dwSize;
            uint32_t dwFlags;
            uint32_t dwFourCC;
            uint32_t dwRGBBitCount;
            uint32_t dwRBitMask;
            uint32_t dwGBitMask;
            uint32_t dwBBitMask;
            uint32_t dwABitMask;
        } ddpf;
        struct {
            uint32_t dwCaps1;
            uint32_t dwCaps2;
            uint32_t dwReserved[2];
        } ddsCaps;
        uint32_t dwReserved2;
    };

    struct DDSHeaderDX10 {
        uint32_t dxgiFormat;
        uint32_t resourceDimension;
        uint32_t miscFlag;
        uint32_t arraySize;
        uint32_t miscFlags2;
    };

    class TextureImporter
    {
    public:
        static void SaveFile(std::filesystem::path const& sourcePath, std::filesystem::path& cachePath);
    private:
        static void SaveDDSFile(const std::string& filePath, int width, int height, const std::vector<uint8_t>& compressedData);
    };
}

#endif
