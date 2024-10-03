#pragma once
#include <Core/Core.hpp>
#include <Assets/Asset.hpp>

//forward declare
namespace FMOD
{
	class Sound;
}

namespace Borealis
{
	using AudioPtr = FMOD::Sound*;

	class Audio : public Asset
	{
	public:
		std::string AudioPath;
		AudioPtr audio = nullptr;
	};
}
